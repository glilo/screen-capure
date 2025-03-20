#include "screen_capture_thread.h"


ScreenCaptureThread::ScreenCaptureThread(const std::string videoSize,
    const std::string offset_x, const std::string offset_y, QObject* parent) 
    : videoSize(videoSize), offset_x(offset_x), offset_y(offset_y), QThread(parent), capturing(true) {}

void ScreenCaptureThread::run() {
    avdevice_register_all(); // Registrar dispositivos

    const AVInputFormat* inputFormat = av_find_input_format("gdigrab"); // Usar GDIgrab en Windows
    if (!inputFormat) {
        qDebug() << "No se encontró el formato de entrada gdigrab.";
        return;
    }

    AVDictionary* options = nullptr;
    av_dict_set(&options, "framerate", "25", 0);
    av_dict_set(&options, "video_size", videoSize.c_str(), 0);
    av_dict_set(&options, "offset_x", offset_x.c_str(), 0);
    av_dict_set(&options, "offset_y", offset_y.c_str(), 0);
    av_dict_set(&options, "show_region", "1", 0);
    std::string screenNames = "desktop";
    int ret = avformat_open_input(&formatContext, screenNames.c_str(), inputFormat, &options);
    if (ret != 0) {
        char errbuf[AV_ERROR_MAX_STRING_SIZE];
        av_strerror(ret, errbuf, sizeof(errbuf));
        qDebug() << "No se pudo abrir la captura de pantalla: " << errbuf;
        return;
    }

    while (capturing) {
        AVPacket packet;
        if (av_read_frame(formatContext, &packet) >= 0) {
            qDebug() << "Frame capturado.";
            av_packet_unref(&packet);
        }
        else {
            qDebug() << "Error capturando frame.";
            break;
        }
    }

    avformat_close_input(&formatContext);
}

void ScreenCaptureThread::stopCapture() {
    capturing = false;
}