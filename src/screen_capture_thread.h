#include <QThread>
#include <QDebug>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavdevice/avdevice.h>
}

class ScreenCaptureThread : public QThread {
    Q_OBJECT

private:
    std::string videoSize;
    std::string offset_x;
    std::string offset_y;
    bool capturing;
    AVFormatContext* formatContext = nullptr;

public:
    explicit ScreenCaptureThread(const std::string videoSize,
        const std::string offset_x, const std::string offset_y, QObject* parent = nullptr);
    void stopCapture();
    void run() override;

};