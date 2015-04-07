#include <sensekit_types.h>
#include "StreamConnection.h"
#include "StreamBin.h"
#include "Stream.h"

namespace sensekit {
    using namespace std::placeholders;

    StreamConnection::StreamConnection(Stream* stream)
        : m_stream(stream)
    {
        assert (stream != nullptr);

        m_connection.handle =
            reinterpret_cast<sensekit_streamconnection_handle_t>(this);

        m_connection.desc = stream->get_description();
    }

    const sensekit_stream_desc_t& StreamConnection::get_description() const
    {
        return m_stream->get_description();
    }

    sensekit_frame_ref_t* StreamConnection::lock()
    {
        if (m_locked)
            return &m_currentFrame;

        m_currentFrame.frame = m_bin->lock_front_buffer();
        m_currentFrame.streamConnection = &m_connection;

        m_locked = true;

        return &m_currentFrame;
    }

    void StreamConnection::unlock()
    {
        if (!m_locked)
            return;

        m_bin->unlock_front_buffer();
        m_locked = true;
    }

    void StreamConnection::start()
    {
        if (m_started)
            return;

        m_started = true;
    }

    void StreamConnection::stop()
    {
        if (!m_started)
            return;

        m_started = false;
    }

    void StreamConnection::set_bin(StreamBin* bin)
    {
        if (m_bin != nullptr)
        {
            m_bin->unregister_front_buffer_ready_callback(m_binFrontBufferReadyCallbackId);
            m_binFrontBufferReadyCallback = nullptr;
            m_bin->dec_connected();
        }

        m_bin = bin;

        if (m_bin != nullptr)
        {
            m_bin->inc_connected();
            
            m_binFrontBufferReadyCallback = std::bind(&StreamConnection::on_bin_front_buffer_ready, this, _1);
            m_binFrontBufferReadyCallbackId = m_bin->register_front_buffer_ready_callback(m_binFrontBufferReadyCallback);
        }
    }

    void StreamConnection::on_bin_front_buffer_ready(StreamBin* bin)
    {
        m_frameReadySignal.raise(this);
    }

    CallbackId StreamConnection::register_frame_ready_callback(SCFrameReadyCallback callback)
    {
        return m_frameReadySignal += callback;
    }

    void StreamConnection::unregister_frame_ready_callback(CallbackId& callbackId)
    {
        m_frameReadySignal -= callbackId;
        callbackId = 0;
    }

    void StreamConnection::set_parameter(sensekit_parameter_id id,
                                         size_t byteLength,
                                         sensekit_parameter_data_t* data)
    {
        m_stream->set_parameter(this, id, byteLength, data);
    }

    void StreamConnection::get_parameter_size(sensekit_parameter_id id,
                                              size_t& byteLength)
    {
        m_stream->get_parameter_size(this, id, byteLength);
    }

    void StreamConnection::get_parameter_data(sensekit_parameter_id id,
                                              size_t byteLength,
                                              sensekit_parameter_data_t* data)
    {
        m_stream->get_parameter_data(this, id, byteLength, data);
    }

    StreamConnection::~StreamConnection()
    {
        set_bin(nullptr);
    }
}
