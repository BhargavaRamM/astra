#ifndef IMAGE_CAPI_H
#define IMAGE_CAPI_H

#include <Astra/astra_defines.h>
#include <Astra/astra_types.h>
#include <AstraUL/streams/image_types.h>

ASTRA_BEGIN_DECLS

ASTRA_API_EX astra_status_t astra_imagestream_get_mirroring(astra_imagestream_t imageStream,
                                                            bool* mirroring);

ASTRA_API_EX astra_status_t astra_imagestream_set_mirroring(astra_imagestream_t imageStream,
                                                            bool mirroring);

ASTRA_API_EX astra_status_t astra_imagestream_get_hfov(astra_imagestream_t imageStream,
                                                       float* hFov);

ASTRA_API_EX astra_status_t astra_imagestream_get_vfov(astra_imagestream_t imageStream,
                                                       float* vFov);

ASTRA_API_EX astra_status_t astra_imagestream_request_modes(astra_imagestream_t imageStream,
                                                            astra_result_token_t* token,
                                                            size_t* count);

ASTRA_API_EX astra_status_t astra_imagestream_get_modes_result(astra_imagestream_t imageStream,
                                                               astra_result_token_t token,
                                                               astra_imagestream_mode_t* modes,
                                                               size_t count);

ASTRA_API_EX astra_status_t astra_imagestream_set_mode(astra_imagestream_t imageStream,
                                                       const astra_imagestream_mode_t* mode);

ASTRA_API_EX astra_status_t astra_reader_get_imageframe(astra_reader_frame_t readerFrame,
                                                        astra_stream_type_t type,
                                                        astra_stream_subtype_t subtype,
                                                        astra_imageframe_t* imageFrame);

ASTRA_API_EX astra_status_t astra_imageframe_get_stream(astra_imageframe_t imageFrame,
                                                        astra_streamconnection_t* stream);

ASTRA_API_EX astra_status_t astra_imageframe_get_frameindex(astra_imageframe_t imageFrame,
                                                            astra_frame_index_t* index);

ASTRA_API_EX astra_status_t astra_imageframe_get_data_byte_length(astra_imageframe_t imageFrame,
                                                                  size_t* byteLength);

ASTRA_API_EX astra_status_t astra_imageframe_get_data_ptr(astra_imageframe_t imageFrame,
                                                          void** data,
                                                          size_t* byteLength);

ASTRA_API_EX astra_status_t astra_imageframe_copy_data(astra_imageframe_t imageFrame,
                                                       void* data);

ASTRA_API_EX astra_status_t astra_imageframe_get_metadata(astra_imageframe_t imageFrame,
                                                          astra_image_metadata_t* metadata );



ASTRA_END_DECLS

#endif // IMAGE_CAPI_H
