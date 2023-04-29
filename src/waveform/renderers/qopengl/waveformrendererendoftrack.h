#pragma once

#include <QColor>
#include <memory>

#include "qopengl/shaders/endoftrackshader.h"
#include "util/class.h"
#include "util/performancetimer.h"
#include "waveform/renderers/qopengl/waveformrenderer.h"

class ControlObject;
class ControlProxy;
class QDomNode;
class SkinContext;

namespace qopengl {
class WaveformRendererEndOfTrack;
}

class qopengl::WaveformRendererEndOfTrack final : public qopengl::WaveformRenderer {
  public:
    explicit WaveformRendererEndOfTrack(
            WaveformWidgetRenderer* waveformWidget);
    ~WaveformRendererEndOfTrack() override;

    void setup(const QDomNode& node, const SkinContext& context) override;

    bool init() override;

    void initializeGL() override;
    void renderGL() override;

  private:
    void fillWithGradient(QColor color);

    EndOfTrackShader m_shader;
    std::unique_ptr<ControlProxy> m_pEndOfTrackControl;
    std::unique_ptr<ControlProxy> m_pTimeRemainingControl;

    QColor m_color;
    PerformanceTimer m_timer;

    DISALLOW_COPY_AND_ASSIGN(WaveformRendererEndOfTrack);
};
