#ifndef BOO_AUDIOVOICE_HPP
#define BOO_AUDIOVOICE_HPP

#include <soxr.h>
#include <list>
#include "boo/audiodev/IAudioVoice.hpp"
#include "AudioMatrix.hpp"

namespace boo
{
class BaseAudioVoiceEngine;
struct AudioVoiceEngineMixInfo;

class AudioVoice : public IAudioVoice
{
    friend class BaseAudioVoiceEngine;

protected:
    /* Mixer-engine relationships */
    BaseAudioVoiceEngine& m_parent;
    std::list<AudioVoice*>::iterator m_parentIt;
    bool m_bound = false;
    void bindVoice(std::list<AudioVoice*>::iterator pIt)
    {
        m_bound = true;
        m_parentIt = pIt;
    }

    /* Callback (audio source) */
    IAudioVoiceCallback* m_cb;

    /* Sample-rate converter */
    soxr_t m_src;
    bool m_dynamicRate;

    /* Running bool */
    bool m_running = false;

    virtual size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, int16_t* buf)=0;
    virtual size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, int32_t* buf)=0;
    virtual size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, float* buf)=0;
    AudioVoice(BaseAudioVoiceEngine& parent, IAudioVoiceCallback* cb, bool dynamicRate);

public:
    ~AudioVoice();

    void setPitchRatio(double ratio);
    void start();
    void stop();
    void unbindVoice();
};

class AudioVoiceMono : public AudioVoice
{
    AudioMatrixMono m_matrix;

    static size_t SRCCallback(AudioVoiceMono* ctx,
                              int16_t** data, size_t requestedLen);

    size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, int16_t* buf);
    size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, int32_t* buf);
    size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, float* buf);

public:
    AudioVoiceMono(BaseAudioVoiceEngine& parent, IAudioVoiceCallback* cb,
                   double sampleRate, bool dynamicRate);
    void setDefaultMatrixCoefficients();
    void setMonoMatrixCoefficients(const float coefs[8]);
    void setStereoMatrixCoefficients(const float coefs[8][2]);
};

class AudioVoiceStereo : public AudioVoice
{
    AudioMatrixStereo m_matrix;

    static size_t SRCCallback(AudioVoiceStereo* ctx,
                              int16_t** data, size_t requestedLen);

    size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, int16_t* buf);
    size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, int32_t* buf);
    size_t pumpAndMix(const AudioVoiceEngineMixInfo& mixInfo, size_t frames, float* buf);

public:
    AudioVoiceStereo(BaseAudioVoiceEngine& parent, IAudioVoiceCallback* cb,
                     double sampleRate, bool dynamicRate);
    void setDefaultMatrixCoefficients();
    void setMonoMatrixCoefficients(const float coefs[8]);
    void setStereoMatrixCoefficients(const float coefs[8][2]);
};

}

#endif // BOO_AUDIOVOICE_HPP