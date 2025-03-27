// original: https://github.com/strukturag/libheif/blob/master/libheif/api/libheif/heif.h
// This file is used for building on Windows.

/*
 * HEIF codec.
 * Copyright (c) 2017-2023 Dirk Farin <dirk.farin@gmail.com>
 *
 * This file is part of libheif.
 *
 * libheif is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * libheif is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libheif.  If not, see <http://www.gnu.org/licenses/>.
 */

struct heif_context;
struct heif_image_handle;
struct heif_image;


enum heif_error_code
{
  // Everything ok, no error occurred.
  heif_error_Ok = 0,

  // Input file does not exist.
  heif_error_Input_does_not_exist = 1,

  // Error in input file. Corrupted or invalid content.
  heif_error_Invalid_input = 2,

  // Input file type is not supported.
  heif_error_Unsupported_filetype = 3,

  // Image requires an unsupported decoder feature.
  heif_error_Unsupported_feature = 4,

  // Library API has been used in an invalid way.
  heif_error_Usage_error = 5,

  // Could not allocate enough memory.
  heif_error_Memory_allocation_error = 6,

  // The decoder plugin generated an error
  heif_error_Decoder_plugin_error = 7,

  // The encoder plugin generated an error
  heif_error_Encoder_plugin_error = 8,

  // Error during encoding or when writing to the output
  heif_error_Encoding_error = 9,

  // Application has asked for a color profile type that does not exist
  heif_error_Color_profile_does_not_exist = 10,

  // Error loading a dynamic plugin
  heif_error_Plugin_loading_error = 11,

  // Operation has been canceled
  heif_error_Canceled = 12
};


enum heif_suberror_code
{
  // no further information available
  heif_suberror_Unspecified = 0,

  // --- Invalid_input ---

  // End of data reached unexpectedly.
  heif_suberror_End_of_data = 100,

  // Size of box (defined in header) is wrong
  heif_suberror_Invalid_box_size = 101,

  // Mandatory 'ftyp' box is missing
  heif_suberror_No_ftyp_box = 102,

  heif_suberror_No_idat_box = 103,

  heif_suberror_No_meta_box = 104,

  heif_suberror_No_hdlr_box = 105,

  heif_suberror_No_hvcC_box = 106,

  heif_suberror_No_pitm_box = 107,

  heif_suberror_No_ipco_box = 108,

  heif_suberror_No_ipma_box = 109,

  heif_suberror_No_iloc_box = 110,

  heif_suberror_No_iinf_box = 111,

  heif_suberror_No_iprp_box = 112,

  heif_suberror_No_iref_box = 113,

  heif_suberror_No_pict_handler = 114,

  // An item property referenced in the 'ipma' box is not existing in the 'ipco' container.
  heif_suberror_Ipma_box_references_nonexisting_property = 115,

  // No properties have been assigned to an item.
  heif_suberror_No_properties_assigned_to_item = 116,

  // Image has no (compressed) data
  heif_suberror_No_item_data = 117,

  // Invalid specification of image grid (tiled image)
  heif_suberror_Invalid_grid_data = 118,

  // Tile-images in a grid image are missing
  heif_suberror_Missing_grid_images = 119,

  heif_suberror_Invalid_clean_aperture = 120,

  // Invalid specification of overlay image
  heif_suberror_Invalid_overlay_data = 121,

  // Overlay image completely outside of visible canvas area
  heif_suberror_Overlay_image_outside_of_canvas = 122,

  heif_suberror_Auxiliary_image_type_unspecified = 123,

  heif_suberror_No_or_invalid_primary_item = 124,

  heif_suberror_No_infe_box = 125,

  heif_suberror_Unknown_color_profile_type = 126,

  heif_suberror_Wrong_tile_image_chroma_format = 127,

  heif_suberror_Invalid_fractional_number = 128,

  heif_suberror_Invalid_image_size = 129,

  heif_suberror_Invalid_pixi_box = 130,

  heif_suberror_No_av1C_box = 131,

  heif_suberror_Wrong_tile_image_pixel_depth = 132,

  heif_suberror_Unknown_NCLX_color_primaries = 133,

  heif_suberror_Unknown_NCLX_transfer_characteristics = 134,

  heif_suberror_Unknown_NCLX_matrix_coefficients = 135,

  // Invalid specification of region item
  heif_suberror_Invalid_region_data = 136,

  // Image has no ispe property
  heif_suberror_No_ispe_property = 137,

  heif_suberror_Camera_intrinsic_matrix_undefined = 138,

  heif_suberror_Camera_extrinsic_matrix_undefined = 139,

  // Invalid JPEG 2000 codestream - usually a missing marker
  heif_suberror_Invalid_J2K_codestream = 140,

  heif_suberror_No_vvcC_box = 141,

  // icbr is only needed in some situations, this error is for those cases
  heif_suberror_No_icbr_box = 142,

  heif_suberror_No_avcC_box = 143,

  // we got a mini box, but could not read it properly
  heif_suberror_Invalid_mini_box = 149,

  // Decompressing generic compression or header compression data failed (e.g. bitstream corruption)
  heif_suberror_Decompression_invalid_data = 150,

  // --- Memory_allocation_error ---

  // A security limit preventing unreasonable memory allocations was exceeded by the input file.
  // Please check whether the file is valid. If it is, contact us so that we could increase the
  // security limits further.
  heif_suberror_Security_limit_exceeded = 1000,

  // There was an error from the underlying compression / decompression library.
  // One possibility is lack of resources (e.g. memory).
  heif_suberror_Compression_initialisation_error = 1001,

  // --- Usage_error ---

  // An item ID was used that is not present in the file.
  heif_suberror_Nonexisting_item_referenced = 2000, // also used for Invalid_input

  // An API argument was given a NULL pointer, which is not allowed for that function.
  heif_suberror_Null_pointer_argument = 2001,

  // Image channel referenced that does not exist in the image
  heif_suberror_Nonexisting_image_channel_referenced = 2002,

  // The version of the passed plugin is not supported.
  heif_suberror_Unsupported_plugin_version = 2003,

  // The version of the passed writer is not supported.
  heif_suberror_Unsupported_writer_version = 2004,

  // The given (encoder) parameter name does not exist.
  heif_suberror_Unsupported_parameter = 2005,

  // The value for the given parameter is not in the valid range.
  heif_suberror_Invalid_parameter_value = 2006,

  // Error in property specification
  heif_suberror_Invalid_property = 2007,

  // Image reference cycle found in iref
  heif_suberror_Item_reference_cycle = 2008,


  // --- Unsupported_feature ---

  // Image was coded with an unsupported compression method.
  heif_suberror_Unsupported_codec = 3000,

  // Image is specified in an unknown way, e.g. as tiled grid image (which is supported)
  heif_suberror_Unsupported_image_type = 3001,

  heif_suberror_Unsupported_data_version = 3002,

  // The conversion of the source image to the requested chroma / colorspace is not supported.
  heif_suberror_Unsupported_color_conversion = 3003,

  heif_suberror_Unsupported_item_construction_method = 3004,

  heif_suberror_Unsupported_header_compression_method = 3005,

  // Generically compressed data used an unsupported compression method
  heif_suberror_Unsupported_generic_compression_method = 3006,

  heif_suberror_Unsupported_essential_property = 3007,

  // --- Encoder_plugin_error ---

  heif_suberror_Unsupported_bit_depth = 4000,


  // --- Encoding_error ---

  heif_suberror_Cannot_write_output_data = 5000,

  heif_suberror_Encoder_initialization = 5001,
  heif_suberror_Encoder_encoding = 5002,
  heif_suberror_Encoder_cleanup = 5003,

  heif_suberror_Too_many_regions = 5004,


  // --- Plugin loading error ---

  heif_suberror_Plugin_loading_error = 6000,         // a specific plugin file cannot be loaded
  heif_suberror_Plugin_is_not_loaded = 6001,         // trying to remove a plugin that is not loaded
  heif_suberror_Cannot_read_plugin_directory = 6002, // error while scanning the directory for plugins
  heif_suberror_No_matching_decoder_installed = 6003 // no decoder found for that compression format
};


struct heif_error
{
  // main error category
  enum heif_error_code code;

  // more detailed error code
  enum heif_suberror_code subcode;

  // textual error message (is always defined, you do not have to check for NULL)
  const char* message;
};

// Default success return value. Intended for use in user-supplied callback functions.
extern const struct heif_error heif_error_success;

typedef uint32_t heif_item_id;
typedef uint32_t heif_property_id;



// ========================= enum types ======================

/**
 * libheif known compression formats.
 */
enum heif_compression_format
{
  /**
   * Unspecified / undefined compression format.
   *
   * This is used to mean "no match" or "any decoder" for some parts of the
   * API. It does not indicate a specific compression format.
   */
  heif_compression_undefined = 0,
  /**
   * HEVC compression, used for HEIC images.
   *
   * This is equivalent to H.265.
  */
  heif_compression_HEVC = 1,
  /**
   * AVC compression. (Currently unused in libheif.)
   *
   * The compression is defined in ISO/IEC 14496-10. This is equivalent to H.264.
   *
   * The encapsulation is defined in ISO/IEC 23008-12:2022 Annex E.
   */
  heif_compression_AVC = 2,
  /**
   * JPEG compression.
   *
   * The compression format is defined in ISO/IEC 10918-1. The encapsulation
   * of JPEG is specified in ISO/IEC 23008-12:2022 Annex H.
  */
  heif_compression_JPEG = 3,
  /**
   * AV1 compression, used for AVIF images.
   *
   * The compression format is provided at https://aomediacodec.github.io/av1-spec/
   *
   * The encapsulation is defined in https://aomediacodec.github.io/av1-avif/
   */
  heif_compression_AV1 = 4,
  /**
   * VVC compression.
   *
   * The compression format is defined in ISO/IEC 23090-3. This is equivalent to H.266.
   *
   * The encapsulation is defined in ISO/IEC 23008-12:2022 Annex L.
   */
  heif_compression_VVC = 5,
  /**
   * EVC compression. (Currently unused in libheif.)
   *
   * The compression format is defined in ISO/IEC 23094-1.
   *
   * The encapsulation is defined in ISO/IEC 23008-12:2022 Annex M.
   */
  heif_compression_EVC = 6,
  /**
   * JPEG 2000 compression.
   *
   * The encapsulation of JPEG 2000 is specified in ISO/IEC 15444-16:2021.
   * The core encoding is defined in ISO/IEC 15444-1, or ITU-T T.800.
  */
  heif_compression_JPEG2000 = 7,
  /**
   * Uncompressed encoding.
   *
   * This is defined in ISO/IEC 23001-17:2024.
  */
  heif_compression_uncompressed = 8,
  /**
   * Mask image encoding.
   *
   * See ISO/IEC 23008-12:2022 Section 6.10.2
   */
  heif_compression_mask = 9,
  /**
   * High Throughput JPEG 2000 (HT-J2K) compression.
   *
   * The encapsulation of HT-J2K is specified in ISO/IEC 15444-16:2021.
   * The core encoding is defined in ISO/IEC 15444-15, or ITU-T T.814.
  */
  heif_compression_HTJ2K = 10
};

enum heif_chroma
{
  heif_chroma_undefined = 99,
  heif_chroma_monochrome = 0,
  heif_chroma_420 = 1,
  heif_chroma_422 = 2,
  heif_chroma_444 = 3,
  heif_chroma_interleaved_RGB = 10,
  heif_chroma_interleaved_RGBA = 11,
  heif_chroma_interleaved_RRGGBB_BE = 12,   // HDR, big endian.
  heif_chroma_interleaved_RRGGBBAA_BE = 13, // HDR, big endian.
  heif_chroma_interleaved_RRGGBB_LE = 14,   // HDR, little endian.
  heif_chroma_interleaved_RRGGBBAA_LE = 15  // HDR, little endian.
};

// DEPRECATED ENUM NAMES

/*
#define heif_chroma_interleaved_24bit  heif_chroma_interleaved_RGB
#define heif_chroma_interleaved_32bit  heif_chroma_interleaved_RGBA
*/

enum heif_colorspace
{
  heif_colorspace_undefined = 99,

  // heif_colorspace_YCbCr should be used with one of these heif_chroma values:
  // * heif_chroma_444
  // * heif_chroma_422
  // * heif_chroma_420
  heif_colorspace_YCbCr = 0,

  // heif_colorspace_RGB should be used with one of these heif_chroma values:
  // * heif_chroma_444 (for planar RGB)
  // * heif_chroma_interleaved_RGB
  // * heif_chroma_interleaved_RGBA
  // * heif_chroma_interleaved_RRGGBB_BE
  // * heif_chroma_interleaved_RRGGBBAA_BE
  // * heif_chroma_interleaved_RRGGBB_LE
  // * heif_chroma_interleaved_RRGGBBAA_LE
  heif_colorspace_RGB = 1,

  // heif_colorspace_monochrome should only be used with heif_chroma = heif_chroma_monochrome
  heif_colorspace_monochrome = 2,

  // Indicates that this image has no visual channels.
  heif_colorspace_nonvisual = 3
};

enum heif_channel
{
  heif_channel_Y = 0,
  heif_channel_Cb = 1,
  heif_channel_Cr = 2,
  heif_channel_R = 3,
  heif_channel_G = 4,
  heif_channel_B = 5,
  heif_channel_Alpha = 6,
  heif_channel_interleaved = 10,
  heif_channel_filter_array = 11,
  heif_channel_depth = 12,
  heif_channel_disparity = 13
};

enum heif_metadata_compression
{
  heif_metadata_compression_off = 0,
  heif_metadata_compression_auto = 1,
  heif_metadata_compression_unknown = 2, // only used when reading unknown method from input file
  heif_metadata_compression_deflate = 3,
  heif_metadata_compression_zlib = 4,    // do not use for header data
  heif_metadata_compression_brotli = 5
};

// ========================= library initialization ======================

struct heif_init_params
{
  int version;

  // currently no parameters
};


/**
 * Initialise library.
 *
 * You should call heif_init() when you start using libheif and heif_deinit() when you are finished.
 * These calls are reference counted. Each call to heif_init() should be matched by one call to heif_deinit().
 *
 * For backwards compatibility, it is not really necessary to call heif_init(), but some library memory objects
 * will never be freed if you do not call heif_init()/heif_deinit().
 *
 * heif_init() will load the external modules installed in the default plugin path. Thus, you need it when you
 * want to load external plugins from the default path.
 * Codec plugins that are compiled into the library directly (selected by the compile-time parameters of libheif)
 * will be available even without heif_init().
 *
 * Make sure that you do not have one part of your program use heif_init()/heif_deinit() and another part that does
 * not use it as the latter may try to use an uninitialized library. If in doubt, enclose everything with init/deinit.
 *
 * You may pass nullptr to get default parameters. Currently, no parameters are supported.
 */
// LIBHEIF_API
struct heif_error heif_init(struct heif_init_params*);

/**
 * Deinitialise and clean up library.
 *
 * You should call heif_init() when you start using libheif and heif_deinit() when you are finished.
 * These calls are reference counted. Each call to heif_init() should be matched by one call to heif_deinit().
 *
 * Note: heif_deinit() must not be called after exit(), for example in a global C++ object's destructor.
 * If you do, global variables in libheif might have already been released when heif_deinit() is running,
 * leading to a crash.
 *
 * \sa heif_init()
 */
// LIBHEIF_API
void heif_deinit(void);


// --- Plugins are currently only supported on Unix platforms.

enum heif_plugin_type
{
  heif_plugin_type_encoder,
  heif_plugin_type_decoder
};

struct heif_plugin_info
{
  int version; // version of this info struct
  enum heif_plugin_type type;
  const void* plugin;
  void* internal_handle; // for internal use only
};

// LIBHEIF_API
struct heif_error heif_load_plugin(const char* filename, struct heif_plugin_info const** out_plugin);

// LIBHEIF_API
struct heif_error heif_load_plugins(const char* directory,
                                    const struct heif_plugin_info** out_plugins,
                                    int* out_nPluginsLoaded,
                                    int output_array_size);

// LIBHEIF_API
struct heif_error heif_unload_plugin(const struct heif_plugin_info* plugin);

// Get a NULL terminated array of the plugin directories that are searched by libheif.
// This includes the paths specified in the environment variable LIBHEIF_PLUGIN_PATHS and the built-in path
// (if not overridden by the environment variable).
// LIBHEIF_API
const char*const* heif_get_plugin_directories(void);

// LIBHEIF_API
void heif_free_plugin_directories(const char*const*);


// ========================= file type check ======================

enum heif_filetype_result
{
  heif_filetype_no,
  heif_filetype_yes_supported,   // it is heif and can be read by libheif
  heif_filetype_yes_unsupported, // it is heif, but cannot be read by libheif
  heif_filetype_maybe // not sure whether it is an heif, try detection with more input data
};

// input data should be at least 12 bytes
// LIBHEIF_API
enum heif_filetype_result heif_check_filetype(const uint8_t* data, int len);

/**
 * Check the filetype box content for a supported file type.
 *
 * <p>The data is assumed to start from the start of the `ftyp` box.
 *
 * <p>This function checks the compatible brands.
 *
 * @returns heif_error_ok if a supported brand is found, or other error if not.
 */
// LIBHEIF_API
struct heif_error heif_has_compatible_filetype(const uint8_t* data, int len);

// LIBHEIF_API
int heif_check_jpeg_filetype(const uint8_t* data, int len);


// DEPRECATED, use heif_brand2 and the heif_brand2_* constants below instead
enum heif_brand
{
  heif_unknown_brand,
  heif_heic, // HEIF image with h265
  heif_heix, // 10bit images, or anything that uses h265 with range extension
  heif_hevc, heif_hevx, // brands for image sequences
  heif_heim, // multiview
  heif_heis, // scalable
  heif_hevm, // multiview sequence
  heif_hevs, // scalable sequence
  heif_mif1, // image, any coding algorithm
  heif_msf1, // sequence, any coding algorithm
  heif_avif, // HEIF image with AV1
  heif_avis,
  heif_vvic, // VVC image
  heif_vvis, // VVC sequence
  heif_evbi, // EVC image
  heif_evbs, // EVC sequence
  heif_j2ki, // JPEG2000 image
  heif_j2is, // JPEG2000 image sequence
};

// input data should be at least 12 bytes
// DEPRECATED, use heif_read_main_brand() instead
// LIBHEIF_API
enum heif_brand heif_main_brand(const uint8_t* data, int len);


typedef uint32_t heif_brand2;

// input data should be at least 12 bytes
// LIBHEIF_API
heif_brand2 heif_read_main_brand(const uint8_t* data, int len);

// input data should be at least 16 bytes
// LIBHEIF_API
heif_brand2 heif_read_minor_version_brand(const uint8_t* data, int len);

// 'brand_fourcc' must be 4 character long, but need not be 0-terminated
// LIBHEIF_API
heif_brand2 heif_fourcc_to_brand(const char* brand_fourcc);

// the output buffer must be at least 4 bytes long
// LIBHEIF_API
void heif_brand_to_fourcc(heif_brand2 brand, char* out_fourcc);

// 'brand_fourcc' must be 4 character long, but need not be 0-terminated
// returns 1 if file includes the brand, and 0 if it does not
// returns -1 if the provided data is not sufficient
//            (you should input at least as many bytes as indicated in the first 4 bytes of the file, usually ~50 bytes will do)
// returns -2 on other errors
// LIBHEIF_API
int heif_has_compatible_brand(const uint8_t* data, int len, const char* brand_fourcc);

// Returns an array of compatible brands. The array is allocated by this function and has to be freed with 'heif_free_list_of_compatible_brands()'.
// The number of entries is returned in out_size.
// LIBHEIF_API
struct heif_error heif_list_compatible_brands(const uint8_t* data, int len, heif_brand2** out_brands, int* out_size);

// LIBHEIF_API
void heif_free_list_of_compatible_brands(heif_brand2* brands_list);


// Returns one of these MIME types:
// - image/heic           HEIF file using h265 compression
// - image/heif           HEIF file using any other compression
// - image/heic-sequence  HEIF image sequence using h265 compression
// - image/heif-sequence  HEIF image sequence using any other compression
// - image/avif           AVIF image
// - image/avif-sequence  AVIF sequence
// - image/jpeg    JPEG image
// - image/png     PNG image
// If the format could not be detected, an empty string is returned.
//
// Provide at least 12 bytes of input. With less input, its format might not
// be detected. You may also provide more input to increase detection accuracy.
//
// Note that JPEG and PNG images cannot be decoded by libheif even though the
// formats are detected by this function.
// LIBHEIF_API
const char* heif_get_file_mime_type(const uint8_t* data, int len);



// ========================= heif_context =========================
// A heif_context represents a HEIF file that has been read.
// In the future, you will also be able to add pictures to a heif_context
// and write it into a file again.


// Allocate a new context for reading HEIF files.
// Has to be freed again with heif_context_free().
// LIBHEIF_API
struct heif_context* heif_context_alloc(void);

// Free a previously allocated HEIF context. You should not free a context twice.
// LIBHEIF_API
void heif_context_free(struct heif_context*);



struct heif_reading_options;

enum heif_reader_grow_status
{
  heif_reader_grow_status_size_reached,    // requested size has been reached, we can read until this point
  heif_reader_grow_status_timeout,         // size has not been reached yet, but it may still grow further (deprecated)
  heif_reader_grow_status_size_beyond_eof, // size has not been reached and never will. The file has grown to its full size
  heif_reader_grow_status_error            // an error has occurred
};

struct heif_reader_range_request_result
{
  enum heif_reader_grow_status status; // should not return 'heif_reader_grow_status_timeout'

  // Indicates up to what position the file has been read.
  // If we cannot read the whole file range (status == 'heif_reader_grow_status_size_beyond_eof'), this is the actual end position.
  // On the other hand, it may be that the reader was reading more data than requested. In that case, it should indicate the full size here
  // and libheif may decide to make use of the additional data (e.g. for filling 'tili' offset tables).
  uint64_t range_end;

  // for status == 'heif_reader_grow_status_error'
  int reader_error_code;        // a reader specific error code
  const char* reader_error_msg; // libheif will call heif_reader.release_error_msg on this if it is not NULL
};


struct heif_reader
{
  // API version supported by this reader
  int reader_api_version;

  // --- version 1 functions ---
  int64_t (* get_position)(void* userdata);

  // The functions read(), and seek() return 0 on success.
  // Generally, libheif will make sure that we do not read past the file size.
  int (* read)(void* data,
               size_t size,
               void* userdata);

  int (* seek)(int64_t position,
               void* userdata);

  // When calling this function, libheif wants to make sure that it can read the file
  // up to 'target_size'. This is useful when the file is currently downloaded and may
  // grow with time. You may, for example, extract the image sizes even before the actual
  // compressed image data has been completely downloaded.
  //
  // Even if your input files will not grow, you will have to implement at least
  // detection whether the target_size is above the (fixed) file length
  // (in this case, return 'size_beyond_eof').
  enum heif_reader_grow_status (* wait_for_file_size)(int64_t target_size, void* userdata);

  // --- version 2 functions ---

  // These two functions are for applications that want to stream HEIF files on demand.
  // For example, a large HEIF file that is served over HTTPS and we only want to download
  // it partially to decode individual tiles.
  // If you do not have this use case, you do not have to implement these functions and
  // you can set them to NULL. For simple linear loading, you may use the 'wait_for_file_size'
  // function above instead.

  // If this function is defined, libheif will often request a file range before accessing it.
  // The purpose of this function is that libheif will usually read very small chunks of data with the
  // read() callback above. However, it is inefficient to request such a small chunk of data over a network
  // and the network delay will significantly increase the decoding time.
  // Thus, libheif will call request_range() with a larger block of data that should be preloaded and the
  // subsequent read() calls will work within the requested ranges.
  //
  // Note: `end_pos` is one byte after the last position to be read.
  // You should return
  // - 'heif_reader_grow_status_size_reached' if the requested range is available, or
  // - 'heif_reader_grow_status_size_beyond_eof' if the requested range exceeds the file size
  //   (the valid part of the range has been read).
  struct heif_reader_range_request_result (*request_range)(uint64_t start_pos, uint64_t end_pos, void* userdata);

  // libheif might issue hints when it assumes that a file range might be needed in the future.
  // This may happen, for example, when your are doing selective tile accesses and libheif proposes
  // to preload offset pointer tables.
  // Another difference to request_file_range() is that this call should be non-blocking.
  // If you preload any data, do this in a background thread.
  void (*preload_range_hint)(uint64_t start_pos, uint64_t end_pos, void* userdata);

  // If libheif does not need access to a file range anymore, it may call this function to
  // give a hint to the reader that it may release the range from a cache.
  // If you do not maintain a file cache that wants to reduce its size dynamically, you do not
  // need to implement this function.
  void (*release_file_range)(uint64_t start_pos, uint64_t end_pos, void* userdata);

  // Release an error message that was returned by heif_reader in an earlier call.
  // If this function is NULL, the error message string will not be released.
  // This is a viable option if you are only returning static strings.
  void (*release_error_msg)(const char* msg);
};


// Read a HEIF file from a named disk file.
// The heif_reading_options should currently be set to NULL.
// LIBHEIF_API
struct heif_error heif_context_read_from_file(struct heif_context*, const char* filename,
                                              const struct heif_reading_options*);

// Read a HEIF file stored completely in memory.
// The heif_reading_options should currently be set to NULL.
// DEPRECATED: use heif_context_read_from_memory_without_copy() instead.
// LIBHEIF_API
struct heif_error heif_context_read_from_memory(struct heif_context*,
                                                const void* mem, size_t size,
                                                const struct heif_reading_options*);

// Same as heif_context_read_from_memory() except that the provided memory is not copied.
// That means, you will have to keep the memory area alive as long as you use the heif_context.
// LIBHEIF_API
struct heif_error heif_context_read_from_memory_without_copy(struct heif_context*,
                                                             const void* mem, size_t size,
                                                             const struct heif_reading_options*);

// LIBHEIF_API
struct heif_error heif_context_read_from_reader(struct heif_context*,
                                                const struct heif_reader* reader,
                                                void* userdata,
                                                const struct heif_reading_options*);

// Number of top-level images in the HEIF file. This does not include the thumbnails or the
// tile images that are composed to an image grid. You can get access to the thumbnails via
// the main image handle.
// LIBHEIF_API
int heif_context_get_number_of_top_level_images(struct heif_context* ctx);

// LIBHEIF_API
int heif_context_is_top_level_image_ID(struct heif_context* ctx, heif_item_id id);

// Fills in image IDs into the user-supplied int-array 'ID_array', preallocated with 'count' entries.
// Function returns the total number of IDs filled into the array.
// LIBHEIF_API
int heif_context_get_list_of_top_level_image_IDs(struct heif_context* ctx,
                                                 heif_item_id* ID_array,
                                                 int count);

// LIBHEIF_API
struct heif_error heif_context_get_primary_image_ID(struct heif_context* ctx, heif_item_id* id);

// Get a handle to the primary image of the HEIF file.
// This is the image that should be displayed primarily when there are several images in the file.
// LIBHEIF_API
struct heif_error heif_context_get_primary_image_handle(struct heif_context* ctx,
                                                        struct heif_image_handle**);

// Get the image handle for a known image ID.
// LIBHEIF_API
struct heif_error heif_context_get_image_handle(struct heif_context* ctx,
                                                heif_item_id id,
                                                struct heif_image_handle**);

// Print information about the boxes of a HEIF file to file descriptor.
// This is for debugging and informational purposes only. You should not rely on
// the output having a specific format. At best, you should not use this at all.
// LIBHEIF_API
void heif_context_debug_dump_boxes_to_file(struct heif_context* ctx, int fd);


// Set the maximum image size security limit. This function will set the maximum image area (number of pixels)
// to maximum_width ^ 2. Alternatively to using this function, you can also set the maximum image area
// in the security limits structure returned by heif_context_get_security_limits().
// LIBHEIF_API
void heif_context_set_maximum_image_size_limit(struct heif_context* ctx, int maximum_width);

// If the maximum threads number is set to 0, the image tiles are decoded in the main thread.
// This is different from setting it to 1, which will generate a single background thread to decode the tiles.
// Note that this setting only affects libheif itself. The codecs itself may still use multi-threaded decoding.
// You can use it, for example, in cases where you are decoding several images in parallel anyway you thus want
// to minimize parallelism in each decoder.
// LIBHEIF_API
void heif_context_set_max_decoding_threads(struct heif_context* ctx, int max_threads);


// --- security limits

// If you set a limit to 0, the limit is disabled.
struct heif_security_limits {
  uint8_t version;

  // --- version 1

  // Limit on the maximum image size to avoid allocating too much memory.
  // For example, setting this to 32768^2 pixels = 1 Gigapixels results
  // in 1.5 GB memory need for YUV-4:2:0 or 4 GB for RGB32.
  uint64_t max_image_size_pixels;
  uint64_t max_number_of_tiles;
  uint32_t max_bayer_pattern_pixels;
  uint32_t max_items;

  uint32_t max_color_profile_size;
  uint64_t max_memory_block_size;

  uint32_t max_components;

  uint32_t max_iloc_extents_per_item;
  uint32_t max_size_entity_group;

  uint32_t max_children_per_box; // for all boxes that are not covered by other limits
};

// The global security limits are the default for new heif_contexts.
// These global limits cannot be changed, but you can override the limits for a specific heif_context.
// LIBHEIF_API
const struct heif_security_limits* heif_get_global_security_limits();

// Returns a set of fully disabled security limits. Use with care and only after user confirmation.
// LIBHEIF_API
const struct heif_security_limits* heif_get_disabled_security_limits();

// Returns the security limits for a heif_context.
// By default, the limits are set to the global limits, but you can change them in the returned object.
// LIBHEIF_API
struct heif_security_limits* heif_context_get_security_limits(const struct heif_context*);

// Overwrites the security limits of a heif_context.
// This is a convenience function to easily copy limits.
// LIBHEIF_API
struct heif_error heif_context_set_security_limits(struct heif_context*, const struct heif_security_limits*);


// ------------------------- item properties -------------------------

enum heif_item_property_type
{
//  heif_item_property_unknown = -1,
  heif_item_property_type_invalid = 0,
};

// Get the heif_property_id for a heif_item_id.
// You may specify which property 'type' you want to receive.
// If you specify 'heif_item_property_type_invalid', all properties associated to that item are returned.
// The number of properties is returned, which are not more than 'count' if (out_list != nullptr).
// By setting out_list==nullptr, you can query the number of properties, 'count' is ignored.
// LIBHEIF_API
int heif_item_get_properties_of_type(const struct heif_context* context,
                                     heif_item_id id,
                                     enum heif_item_property_type type,
                                     heif_property_id* out_list,
                                     int count);

// Returns all transformative properties in the correct order.
// This includes "irot", "imir", "clap".
// The number of properties is returned, which are not more than 'count' if (out_list != nullptr).
// By setting out_list==nullptr, you can query the number of properties, 'count' is ignored.
// LIBHEIF_API
int heif_item_get_transformation_properties(const struct heif_context* context,
                                            heif_item_id id,
                                            heif_property_id* out_list,
                                            int count);

// LIBHEIF_API
enum heif_item_property_type heif_item_get_property_type(const struct heif_context* context,
                                                         heif_item_id id,
                                                         heif_property_id property_id);

// The strings are managed by libheif. They will be deleted in heif_property_user_description_release().
struct heif_property_user_description
{
  int version;

  // version 1

  const char* lang;
  const char* name;
  const char* description;
  const char* tags;
};

// Get the "udes" user description property content.
// Undefined strings are returned as empty strings.
// LIBHEIF_API
struct heif_error heif_item_get_property_user_description(const struct heif_context* context,
                                                          heif_item_id itemId,
                                                          heif_property_id propertyId,
                                                          struct heif_property_user_description** out);

// Add a "udes" user description property to the item.
// If any string pointers are NULL, an empty string will be used instead.
// LIBHEIF_API
struct heif_error heif_item_add_property_user_description(const struct heif_context* context,
                                                          heif_item_id itemId,
                                                          const struct heif_property_user_description* description,
                                                          heif_property_id* out_propertyId);

// Release all strings and the object itself.
// Only call for objects that you received from heif_item_get_property_user_description().
// LIBHEIF_API
void heif_property_user_description_release(struct heif_property_user_description*);

enum heif_transform_mirror_direction
{
  heif_transform_mirror_direction_invalid = -1,
  heif_transform_mirror_direction_vertical = 0,    // flip image vertically
  heif_transform_mirror_direction_horizontal = 1   // flip image horizontally
};

// Will return 'heif_transform_mirror_direction_invalid' in case of error.
// LIBHEIF_API
enum heif_transform_mirror_direction heif_item_get_property_transform_mirror(const struct heif_context* context,
                                                                             heif_item_id itemId,
                                                                             heif_property_id propertyId);

// Returns only 0, 90, 180, or 270 angle values.
// Returns -1 in case of error (but it will only return an error in case of wrong usage).
// LIBHEIF_API
int heif_item_get_property_transform_rotation_ccw(const struct heif_context* context,
                                                  heif_item_id itemId,
                                                  heif_property_id propertyId);

// Returns the number of pixels that should be removed from the four edges.
// Because of the way this data is stored, you have to pass the image size at the moment of the crop operation
// to compute the cropped border sizes.
// LIBHEIF_API
void heif_item_get_property_transform_crop_borders(const struct heif_context* context,
                                                   heif_item_id itemId,
                                                   heif_property_id propertyId,
                                                   int image_width, int image_height,
                                                   int* left, int* top, int* right, int* bottom);

/**
 * @param context     The heif_context for the file
 * @param itemId      The image item id to which this property belongs.
 * @param fourcc_type The short four-cc type of the property to add.
 * @param uuid_type   If fourcc_type=='uuid', this should point to a 16-byte UUID type. It is ignored otherwise and can be NULL.
 * @param data        Data to insert for this property (including a full-box header, if required for this box).
 * @param size        Length of data in bytes.
 * @param is_essential   Whether this property is essential (boolean).
 * @param out_propertyId Outputs the id of the inserted property. Can be NULL.
*/
// LIBHEIF_API
struct heif_error heif_item_add_raw_property(const struct heif_context* context,
                                             heif_item_id itemId,
                                             uint32_t fourcc_type,
                                             const uint8_t* uuid_type,
                                             const uint8_t* data, size_t size,
                                             int is_essential,
                                             heif_property_id* out_propertyId);

// LIBHEIF_API
struct heif_error heif_item_get_property_raw_size(const struct heif_context* context,
                                                  heif_item_id itemId,
                                                  heif_property_id propertyId,
                                                  size_t* out_size);

/**
 * @param out_data User-supplied array to write the property data to. The required size of the output array is given by heif_item_get_property_raw_size().
*/
// LIBHEIF_API
struct heif_error heif_item_get_property_raw_data(const struct heif_context* context,
                                                  heif_item_id itemId,
                                                  heif_property_id propertyId,
                                                  uint8_t* out_data);

/**
 * Get the extended type for an extended "uuid" box.
 *
 * This provides the UUID for the extended box.
 *
 * This method should only be called on properties of type `heif_item_property_type_uuid`.
 *
 * @param context the heif_context containing the HEIF file
 * @param itemId the image item id to which this property belongs.
 * @param propertyId the property index (1-based) to get the extended type for
 * @param out_extended_type output of the call, must be a pointer to at least 16-bytes.
 * @return heif_error_success or an error indicating the failure
 */
// LIBHEIF_API
struct heif_error heif_item_get_property_uuid_type(const struct heif_context* context,
                                                   heif_item_id itemId,
                                                   heif_property_id propertyId,
                                                   uint8_t out_extended_type[16]);

// ========================= heif_image_handle =========================

// An heif_image_handle is a handle to a logical image in the HEIF file.
// To get the actual pixel data, you have to decode the handle to an heif_image.
// An heif_image_handle also gives you access to the thumbnails and Exif data
// associated with an image.

// Once you obtained an heif_image_handle, you can already release the heif_context,
// since it is internally ref-counted.

// Release image handle.
// LIBHEIF_API
void heif_image_handle_release(const struct heif_image_handle*);

// Check whether the given image_handle is the primary image of the file.
// LIBHEIF_API
int heif_image_handle_is_primary_image(const struct heif_image_handle* handle);

// LIBHEIF_API
heif_item_id heif_image_handle_get_item_id(const struct heif_image_handle* handle);

// Get the resolution of an image.
// LIBHEIF_API
int heif_image_handle_get_width(const struct heif_image_handle* handle);

// LIBHEIF_API
int heif_image_handle_get_height(const struct heif_image_handle* handle);

// LIBHEIF_API
int heif_image_handle_has_alpha_channel(const struct heif_image_handle*);

// LIBHEIF_API
int heif_image_handle_is_premultiplied_alpha(const struct heif_image_handle*);

// Returns -1 on error, e.g. if this information is not present in the image.
// Only defined for images coded in the YCbCr or monochrome colorspace.
// LIBHEIF_API
int heif_image_handle_get_luma_bits_per_pixel(const struct heif_image_handle*);

// Returns -1 on error, e.g. if this information is not present in the image.
// Only defined for images coded in the YCbCr colorspace.
// LIBHEIF_API
int heif_image_handle_get_chroma_bits_per_pixel(const struct heif_image_handle*);

// Return the colorspace that libheif proposes to use for decoding.
// Usually, these will be either YCbCr or Monochrome, but it may also propose RGB for images
// encoded with matrix_coefficients=0 or for images coded natively in RGB.
// It may also return *_undefined if the file misses relevant information to determine this without decoding.
// These are only proposed values that avoid colorspace conversions as much as possible.
// You can still request the output in your preferred colorspace, but this may involve an internal conversion.
// LIBHEIF_API
struct heif_error heif_image_handle_get_preferred_decoding_colorspace(const struct heif_image_handle* image_handle,
                                                                      enum heif_colorspace* out_colorspace,
                                                                      enum heif_chroma* out_chroma);

// Get the image width from the 'ispe' box. This is the original image size without
// any transformations applied to it. Do not use this unless you know exactly what
// you are doing.
// LIBHEIF_API
int heif_image_handle_get_ispe_width(const struct heif_image_handle* handle);

// LIBHEIF_API
int heif_image_handle_get_ispe_height(const struct heif_image_handle* handle);

// This gets the context associated with the image handle.
// Note that you have to release the returned context with heif_context_free() in any case.
//
// This means: when you have several image-handles that originate from the same file and you get the
// context of each of them, the returned pointer may be different even though it refers to the same
// logical context. You have to call heif_context_free() on all those context pointers.
// After you freed a context pointer, you can still use the context through a different pointer that you
// might have acquired from elsewhere.
// LIBHEIF_API
struct heif_context* heif_image_handle_get_context(const struct heif_image_handle* handle);


struct heif_image_tiling
{
  int version;

  // --- version 1

  uint32_t num_columns;
  uint32_t num_rows;
  uint32_t tile_width;
  uint32_t tile_height;

  uint32_t image_width;
  uint32_t image_height;

  // Position of the top left tile.
  // Usually, this is (0;0), but if a tiled image is rotated or cropped, it may be that the top left tile should be placed at a negative position.
  // The offsets define this negative shift.
  uint32_t top_offset;
  uint32_t left_offset;

  uint8_t number_of_extra_dimensions;  // 0 for normal images, 1 for volumetric (3D), ...
  uint32_t extra_dimension_size[8];    // size of extra dimensions (first 8 dimensions)
};


// If 'process_image_transformations' is true, this returns modified sizes.
// If it is false, the top_offset and left_offset will always be (0;0).
// LIBHEIF_API
struct heif_error heif_image_handle_get_image_tiling(const struct heif_image_handle* handle, int process_image_transformations, struct heif_image_tiling* out_tiling);


// For grid images, return the image item ID of a specific grid tile.
// If 'process_image_transformations' is true, the tile positions are given in the transformed image coordinate system and
// are internally mapped to the original image tile positions.
// LIBHEIF_API
struct heif_error heif_image_handle_get_grid_image_tile_id(const struct heif_image_handle* handle,
                                                           int process_image_transformations,
                                                           uint32_t tile_x, uint32_t tile_y,
                                                           heif_item_id* out_tile_item_id);


struct heif_decoding_options;

// The tile position is given in tile indices, not in pixel coordinates.
// If the image transformations are processed (option->ignore_image_transformations==false), the tile position
// is given in the transformed coordinates.
// LIBHEIF_API
struct heif_error heif_image_handle_decode_image_tile(const struct heif_image_handle* in_handle,
                                                      struct heif_image** out_img,
                                                      enum heif_colorspace colorspace,
                                                      enum heif_chroma chroma,
                                                      const struct heif_decoding_options* options,
                                                      uint32_t tile_x, uint32_t tile_y);


// ------------------------- entity groups ------------------------

typedef uint32_t heif_entity_group_id;

struct heif_entity_group
{
  heif_entity_group_id entity_group_id;
  uint32_t entity_group_type;  // this is a FourCC constant
  heif_item_id* entities;
  uint32_t num_entities;
};

// Use 0 for `type_filter` or `item_filter` to disable the filter.
// Returns an array of heif_entity_group structs with *out_num_groups entries.
// LIBHEIF_API
struct heif_entity_group* heif_context_get_entity_groups(const struct heif_context*,
                                                         uint32_t type_filter,
                                                         heif_item_id item_filter,
                                                         int* out_num_groups);

// Release an array of entity groups returned by heif_context_get_entity_groups().
// LIBHEIF_API
void heif_entity_groups_release(struct heif_entity_group*, int num_groups);


// ------------------------- depth images -------------------------

// LIBHEIF_API
int heif_image_handle_has_depth_image(const struct heif_image_handle*);

// LIBHEIF_API
int heif_image_handle_get_number_of_depth_images(const struct heif_image_handle* handle);

// LIBHEIF_API
int heif_image_handle_get_list_of_depth_image_IDs(const struct heif_image_handle* handle,
                                                  heif_item_id* ids, int count);

// LIBHEIF_API
struct heif_error heif_image_handle_get_depth_image_handle(const struct heif_image_handle* handle,
                                                           heif_item_id depth_image_id,
                                                           struct heif_image_handle** out_depth_handle);


enum heif_depth_representation_type
{
  heif_depth_representation_type_uniform_inverse_Z = 0,
  heif_depth_representation_type_uniform_disparity = 1,
  heif_depth_representation_type_uniform_Z = 2,
  heif_depth_representation_type_nonuniform_disparity = 3
};

struct heif_depth_representation_info
{
  uint8_t version;

  // version 1 fields

  uint8_t has_z_near;
  uint8_t has_z_far;
  uint8_t has_d_min;
  uint8_t has_d_max;

  double z_near;
  double z_far;
  double d_min;
  double d_max;

  enum heif_depth_representation_type depth_representation_type;
  uint32_t disparity_reference_view;

  uint32_t depth_nonlinear_representation_model_size;
  uint8_t* depth_nonlinear_representation_model;

  // version 2 fields below
};


// LIBHEIF_API
void heif_depth_representation_info_free(const struct heif_depth_representation_info* info);

// Returns true when there is depth_representation_info available
// Note 1: depth_image_id is currently unused because we support only one depth channel per image, but
// you should still provide the correct ID for future compatibility.
// Note 2: Because of an API bug before v1.11.0, the function also works when 'handle' is the handle of the depth image.
// However, you should pass the handle of the main image. Please adapt your code if needed.
// LIBHEIF_API
int heif_image_handle_get_depth_image_representation_info(const struct heif_image_handle* handle,
                                                          heif_item_id depth_image_id,
                                                          const struct heif_depth_representation_info** out);



// ------------------------- thumbnails -------------------------

// List the number of thumbnails assigned to this image handle. Usually 0 or 1.
// LIBHEIF_API
int heif_image_handle_get_number_of_thumbnails(const struct heif_image_handle* handle);

// LIBHEIF_API
int heif_image_handle_get_list_of_thumbnail_IDs(const struct heif_image_handle* handle,
                                                heif_item_id* ids, int count);

// Get the image handle of a thumbnail image.
// LIBHEIF_API
struct heif_error heif_image_handle_get_thumbnail(const struct heif_image_handle* main_image_handle,
                                                  heif_item_id thumbnail_id,
                                                  struct heif_image_handle** out_thumbnail_handle);


// ------------------------- auxiliary images -------------------------

/*
#define LIBHEIF_AUX_IMAGE_FILTER_OMIT_ALPHA (1UL<<1)
#define LIBHEIF_AUX_IMAGE_FILTER_OMIT_DEPTH (2UL<<1)
*/

// List the number of auxiliary images assigned to this image handle.
// LIBHEIF_API
int heif_image_handle_get_number_of_auxiliary_images(const struct heif_image_handle* handle,
                                                     int aux_filter);

// LIBHEIF_API
int heif_image_handle_get_list_of_auxiliary_image_IDs(const struct heif_image_handle* handle,
                                                      int aux_filter,
                                                      heif_item_id* ids, int count);

// You are responsible to deallocate the returned buffer with heif_image_handle_release_auxiliary_type().
// LIBHEIF_API
struct heif_error heif_image_handle_get_auxiliary_type(const struct heif_image_handle* handle,
                                                       const char** out_type);

// LIBHEIF_API
void heif_image_handle_release_auxiliary_type(const struct heif_image_handle* handle,
                                              const char** out_type);

// DEPRECATED (because typo in function name). Use heif_image_handle_release_auxiliary_type() instead.
// LIBHEIF_API
void heif_image_handle_free_auxiliary_types(const struct heif_image_handle* handle,
                                            const char** out_type);

// Get the image handle of an auxiliary image.
// LIBHEIF_API
struct heif_error heif_image_handle_get_auxiliary_image_handle(const struct heif_image_handle* main_image_handle,
                                                               heif_item_id auxiliary_id,
                                                               struct heif_image_handle** out_auxiliary_handle);


// ------------------------- metadata (Exif / XMP) -------------------------

// How many metadata blocks are attached to an image. If you only want to get EXIF data,
// set the type_filter to "Exif". Otherwise, set the type_filter to NULL.
// LIBHEIF_API
int heif_image_handle_get_number_of_metadata_blocks(const struct heif_image_handle* handle,
                                                    const char* type_filter);

// 'type_filter' can be used to get only metadata of specific types, like "Exif".
// If 'type_filter' is NULL, it will return all types of metadata IDs.
// LIBHEIF_API
int heif_image_handle_get_list_of_metadata_block_IDs(const struct heif_image_handle* handle,
                                                     const char* type_filter,
                                                     heif_item_id* ids, int count);

// Return a string indicating the type of the metadata, as specified in the HEIF file.
// Exif data will have the type string "Exif".
// This string will be valid until the next call to a libheif function.
// You do not have to free this string.
// LIBHEIF_API
const char* heif_image_handle_get_metadata_type(const struct heif_image_handle* handle,
                                                heif_item_id metadata_id);

// For EXIF, the content type is empty.
// For XMP, the content type is "application/rdf+xml".
// LIBHEIF_API
const char* heif_image_handle_get_metadata_content_type(const struct heif_image_handle* handle,
                                                        heif_item_id metadata_id);

// Get the size of the raw metadata, as stored in the HEIF file.
// LIBHEIF_API
size_t heif_image_handle_get_metadata_size(const struct heif_image_handle* handle,
                                           heif_item_id metadata_id);

// 'out_data' must point to a memory area of the size reported by heif_image_handle_get_metadata_size().
// The data is returned exactly as stored in the HEIF file.
// For Exif data, you probably have to skip the first four bytes of the data, since they
// indicate the offset to the start of the TIFF header of the Exif data.
// LIBHEIF_API
struct heif_error heif_image_handle_get_metadata(const struct heif_image_handle* handle,
                                                 heif_item_id metadata_id,
                                                 void* out_data);

// Only valid for item type == "uri ", an absolute URI
// LIBHEIF_API
const char* heif_image_handle_get_metadata_item_uri_type(const struct heif_image_handle* handle,
                                                         heif_item_id metadata_id);

// ------------------------- color profiles -------------------------

enum heif_color_profile_type
{
  heif_color_profile_type_not_present = 0,
//  heif_color_profile_type_nclx = heif_fourcc('n', 'c', 'l', 'x'),
//  heif_color_profile_type_rICC = heif_fourcc('r', 'I', 'C', 'C'),
//  heif_color_profile_type_prof = heif_fourcc('p', 'r', 'o', 'f')
};


// Returns 'heif_color_profile_type_not_present' if there is no color profile.
// If there is an ICC profile and an NCLX profile, the ICC profile is returned.
// TO-DO: we need a new API for this function as images can contain both NCLX and ICC at the same time.
//       However, you can still use heif_image_handle_get_raw_color_profile() and
//       heif_image_handle_get_nclx_color_profile() to access both profiles.
// LIBHEIF_API
enum heif_color_profile_type heif_image_handle_get_color_profile_type(const struct heif_image_handle* handle);

// LIBHEIF_API
size_t heif_image_handle_get_raw_color_profile_size(const struct heif_image_handle* handle);

// Returns 'heif_error_Color_profile_does_not_exist' when there is no ICC profile.
// LIBHEIF_API
struct heif_error heif_image_handle_get_raw_color_profile(const struct heif_image_handle* handle,
                                                          void* out_data);


enum heif_color_primaries
{
  heif_color_primaries_ITU_R_BT_709_5 = 1, // g=0.3;0.6, b=0.15;0.06, r=0.64;0.33, w=0.3127,0.3290
  heif_color_primaries_unspecified = 2,
  heif_color_primaries_ITU_R_BT_470_6_System_M = 4,
  heif_color_primaries_ITU_R_BT_470_6_System_B_G = 5,
  heif_color_primaries_ITU_R_BT_601_6 = 6,
  heif_color_primaries_SMPTE_240M = 7,
  heif_color_primaries_generic_film = 8,
  heif_color_primaries_ITU_R_BT_2020_2_and_2100_0 = 9,
  heif_color_primaries_SMPTE_ST_428_1 = 10,
  heif_color_primaries_SMPTE_RP_431_2 = 11,
  heif_color_primaries_SMPTE_EG_432_1 = 12,
  heif_color_primaries_EBU_Tech_3213_E = 22
};

enum heif_transfer_characteristics
{
  heif_transfer_characteristic_ITU_R_BT_709_5 = 1,
  heif_transfer_characteristic_unspecified = 2,
  heif_transfer_characteristic_ITU_R_BT_470_6_System_M = 4,
  heif_transfer_characteristic_ITU_R_BT_470_6_System_B_G = 5,
  heif_transfer_characteristic_ITU_R_BT_601_6 = 6,
  heif_transfer_characteristic_SMPTE_240M = 7,
  heif_transfer_characteristic_linear = 8,
  heif_transfer_characteristic_logarithmic_100 = 9,
  heif_transfer_characteristic_logarithmic_100_sqrt10 = 10,
  heif_transfer_characteristic_IEC_61966_2_4 = 11,
  heif_transfer_characteristic_ITU_R_BT_1361 = 12,
  heif_transfer_characteristic_IEC_61966_2_1 = 13,
  heif_transfer_characteristic_ITU_R_BT_2020_2_10bit = 14,
  heif_transfer_characteristic_ITU_R_BT_2020_2_12bit = 15,
  heif_transfer_characteristic_ITU_R_BT_2100_0_PQ = 16,
  heif_transfer_characteristic_SMPTE_ST_428_1 = 17,
  heif_transfer_characteristic_ITU_R_BT_2100_0_HLG = 18
};

enum heif_matrix_coefficients
{
  heif_matrix_coefficients_RGB_GBR = 0,
  heif_matrix_coefficients_ITU_R_BT_709_5 = 1,  // TO-DO: or 709-6 according to h.273
  heif_matrix_coefficients_unspecified = 2,
  heif_matrix_coefficients_US_FCC_T47 = 4,
  heif_matrix_coefficients_ITU_R_BT_470_6_System_B_G = 5,
  heif_matrix_coefficients_ITU_R_BT_601_6 = 6,  // TO-DO: or 601-7 according to h.273
  heif_matrix_coefficients_SMPTE_240M = 7,
  heif_matrix_coefficients_YCgCo = 8,
  heif_matrix_coefficients_ITU_R_BT_2020_2_non_constant_luminance = 9,
  heif_matrix_coefficients_ITU_R_BT_2020_2_constant_luminance = 10,
  heif_matrix_coefficients_SMPTE_ST_2085 = 11,
  heif_matrix_coefficients_chromaticity_derived_non_constant_luminance = 12,
  heif_matrix_coefficients_chromaticity_derived_constant_luminance = 13,
  heif_matrix_coefficients_ICtCp = 14
};

struct heif_color_profile_nclx
{
  // === version 1 fields

  uint8_t version;

  enum heif_color_primaries color_primaries;
  enum heif_transfer_characteristics transfer_characteristics;
  enum heif_matrix_coefficients matrix_coefficients;
  uint8_t full_range_flag;

  // --- decoded values (not used when saving nclx)

  float color_primary_red_x, color_primary_red_y;
  float color_primary_green_x, color_primary_green_y;
  float color_primary_blue_x, color_primary_blue_y;
  float color_primary_white_x, color_primary_white_y;
};

// LIBHEIF_API
struct heif_error heif_nclx_color_profile_set_color_primaries(struct heif_color_profile_nclx* nclx, uint16_t cp);

// LIBHEIF_API
struct heif_error heif_nclx_color_profile_set_transfer_characteristics(struct heif_color_profile_nclx* nclx, uint16_t transfer_characteristics);

// LIBHEIF_API
struct heif_error heif_nclx_color_profile_set_matrix_coefficients(struct heif_color_profile_nclx* nclx, uint16_t matrix_coefficients);

// Returns 'heif_error_Color_profile_does_not_exist' when there is no NCLX profile.
// TO-DO: This function does currently not return an NCLX profile if it is stored in the image bitstream.
//       Only NCLX profiles stored as colr boxes are returned. This may change in the future.
// LIBHEIF_API
struct heif_error heif_image_handle_get_nclx_color_profile(const struct heif_image_handle* handle,
                                                           struct heif_color_profile_nclx** out_data);

// Returned color profile has 'version' field set to the maximum allowed.
// Do not fill values for higher versions as these might be outside the allocated structure size.
// May return NULL.
// LIBHEIF_API
struct heif_color_profile_nclx* heif_nclx_color_profile_alloc(void);

// LIBHEIF_API
void heif_nclx_color_profile_free(struct heif_color_profile_nclx* nclx_profile);

// Note: in early versions of HEIF, there could only be one color profile per image. However, this has been changed.
// This function will now return ICC if one is present and NCLX only if there is no ICC.
// You may better avoid this function and simply query for NCLX and ICC directly.
// LIBHEIF_API
enum heif_color_profile_type heif_image_get_color_profile_type(const struct heif_image* image);

// Returns the size of the ICC profile if one is assigned to the image. Otherwise, it returns 0.
// LIBHEIF_API
size_t heif_image_get_raw_color_profile_size(const struct heif_image* image);

// Returns the ICC profile if one is assigned to the image. Otherwise, it returns an error.
// LIBHEIF_API
struct heif_error heif_image_get_raw_color_profile(const struct heif_image* image,
                                                   void* out_data);

// LIBHEIF_API
struct heif_error heif_image_get_nclx_color_profile(const struct heif_image* image,
                                                    struct heif_color_profile_nclx** out_data);


// ------------------------- intrinsic and extrinsic matrices -------------------------

struct heif_camera_intrinsic_matrix
{
  double focal_length_x;
  double focal_length_y;
  double principal_point_x;
  double principal_point_y;
  double skew;
};


// LIBHEIF_API
int heif_image_handle_has_camera_intrinsic_matrix(const struct heif_image_handle* handle);

// LIBHEIF_API
struct heif_error heif_image_handle_get_camera_intrinsic_matrix(const struct heif_image_handle* handle,
                                                                struct heif_camera_intrinsic_matrix* out_matrix);


struct heif_camera_extrinsic_matrix;

// LIBHEIF_API
int heif_image_handle_has_camera_extrinsic_matrix(const struct heif_image_handle* handle);

// LIBHEIF_API
struct heif_error heif_image_handle_get_camera_extrinsic_matrix(const struct heif_image_handle* handle,
                                                                struct heif_camera_extrinsic_matrix** out_matrix);

// LIBHEIF_API
void heif_camera_extrinsic_matrix_release(struct heif_camera_extrinsic_matrix*);

// LIBHEIF_API
struct heif_error heif_camera_extrinsic_matrix_get_rotation_matrix(const struct heif_camera_extrinsic_matrix*,
                                                                   double* out_matrix_row_major);



// ========================= heif_image =========================

// An heif_image contains a decoded pixel image in various colorspaces, chroma formats,
// and bit depths.

// Note: when converting images to an interleaved chroma format, the resulting
// image contains only a single channel of type channel_interleaved with, e.g., 3 bytes per pixel,
// containing the interleaved R,G,B values.

// Planar RGB images are specified as heif_colorspace_RGB / heif_chroma_444.

enum heif_progress_step
{
  heif_progress_step_total = 0,
  heif_progress_step_load_tile = 1
};


enum heif_chroma_downsampling_algorithm
{
  heif_chroma_downsampling_nearest_neighbor = 1,
  heif_chroma_downsampling_average = 2,

  // Combine with 'heif_chroma_upsampling_bilinear' for best quality.
  // Makes edges look sharper when using YUV 420 with bilinear chroma upsampling.
  heif_chroma_downsampling_sharp_yuv = 3
};

enum heif_chroma_upsampling_algorithm
{
  heif_chroma_upsampling_nearest_neighbor = 1,
  heif_chroma_upsampling_bilinear = 2
};


struct heif_color_conversion_options
{
  // 'version' must be 1.
  uint8_t version;

  // --- version 1 options

  enum heif_chroma_downsampling_algorithm preferred_chroma_downsampling_algorithm;
  enum heif_chroma_upsampling_algorithm preferred_chroma_upsampling_algorithm;

  // When set to 'false' libheif may also use a different algorithm if the preferred one is not available
  // or using a different algorithm is computationally less complex. Note that currently (v1.17.0) this
  // means that for RGB input it will usually choose nearest-neighbor sampling because this is computationally
  // the simplest.
  // Set this field to 'true' if you want to make sure that the specified algorithm is used even
  // at the cost of slightly higher computation times.
  uint8_t only_use_preferred_chroma_algorithm;

  // --- Note that we cannot extend this struct because it is embedded in
  //     other structs (heif_decoding_options and heif_encoding_options).
};

// Assumes that it is a version=1 struct.
// LIBHEIF_API
void heif_color_conversion_options_set_defaults(struct heif_color_conversion_options*);


struct heif_decoding_options
{
  uint8_t version;

  // version 1 options

  // Ignore geometric transformations like cropping, rotation, mirroring.
  // Default: false (do not ignore).
  uint8_t ignore_transformations;

  // Any of the progress functions may be called from background threads.
  void (* start_progress)(enum heif_progress_step step, int max_progress, void* progress_user_data);

  void (* on_progress)(enum heif_progress_step step, int progress, void* progress_user_data);

  void (* end_progress)(enum heif_progress_step step, void* progress_user_data);

  void* progress_user_data;

  // version 2 options

  uint8_t convert_hdr_to_8bit;

  // version 3 options

  // When enabled, an error is returned for invalid input. Otherwise, it will try its best and
  // add decoding warnings to the decoded heif_image. Default is non-strict.
  uint8_t strict_decoding;

  // version 4 options

  // name_id of the decoder to use for the decoding.
  // If set to NULL (default), the highest priority decoder is chosen.
  // The priority is defined in the plugin.
  const char* decoder_id;

  // version 5 options

  struct heif_color_conversion_options color_conversion_options;

  // version 6 options

  int (* cancel_decoding)(void* progress_user_data);
};


// Allocate decoding options and fill with default values.
// Note: you should always get the decoding options through this function since the
// option structure may grow in size in future versions.
// LIBHEIF_API
struct heif_decoding_options* heif_decoding_options_alloc(void);

// LIBHEIF_API
void heif_decoding_options_free(struct heif_decoding_options*);

// Decode an heif_image_handle into the actual pixel image and also carry out
// all geometric transformations specified in the HEIF file (rotation, cropping, mirroring).
//
// If colorspace or chroma is set to heif_colorspace_undefined or heif_chroma_undefined,
// respectively, the original colorspace is taken.
// Decoding options may be NULL. If you want to supply options, always use
// heif_decoding_options_alloc() to get the structure.
// LIBHEIF_API
struct heif_error heif_decode_image(const struct heif_image_handle* in_handle,
                                    struct heif_image** out_img,
                                    enum heif_colorspace colorspace,
                                    enum heif_chroma chroma,
                                    const struct heif_decoding_options* options);

// Get the colorspace format of the image.
// LIBHEIF_API
enum heif_colorspace heif_image_get_colorspace(const struct heif_image*);

// Get the chroma format of the image.
// LIBHEIF_API
enum heif_chroma heif_image_get_chroma_format(const struct heif_image*);

/**
 * Get the width of a specified image channel.
 *
 * @param img the image to get the width for
 * @param channel the channel to select
 * @return the width of the channel in pixels, or -1 the channel does not exist in the image
 */
// LIBHEIF_API
int heif_image_get_width(const struct heif_image* img, enum heif_channel channel);

/**
 * Get the height of a specified image channel.
 *
 * @param img the image to get the height for
 * @param channel the channel to select
 * @return the height of the channel in pixels, or -1 the channel does not exist in the image
 */
// LIBHEIF_API
int heif_image_get_height(const struct heif_image* img, enum heif_channel channel);

/**
 * Get the width of the main channel.
 *
 * This is the Y channel in YCbCr or mono, or any in RGB.
 *
 * @param img the image to get the primary width for
 * @return the width in pixels
 */
// LIBHEIF_API
int heif_image_get_primary_width(const struct heif_image* img);

/**
 * Get the height of the main channel.
 *
 * This is the Y channel in YCbCr or mono, or any in RGB.
 *
 * @param img the image to get the primary height for
 * @return the height in pixels
 */
// LIBHEIF_API
int heif_image_get_primary_height(const struct heif_image* img);

// LIBHEIF_API
struct heif_error heif_image_crop(struct heif_image* img,
                                  int left, int right, int top, int bottom);

// Get the number of bits per pixel in the given image channel. Returns -1 if
// a non-existing channel was given.
// Note that the number of bits per pixel may be different for each color channel.
// This function returns the number of bits used for storage of each pixel.
// Especially for HDR images, this is probably not what you want. Have a look at
// heif_image_get_bits_per_pixel_range() instead.
// LIBHEIF_API
int heif_image_get_bits_per_pixel(const struct heif_image*, enum heif_channel channel);

// Get the number of bits per pixel in the given image channel. This function returns
// the number of bits used for representing the pixel value, which might be smaller
// than the number of bits used in memory.
// For example, in 12bit HDR images, this function returns '12', while still 16 bits
// are reserved for storage. For interleaved RGBA with 12 bit, this function also returns
// '12', not '48' or '64' (heif_image_get_bits_per_pixel returns 64 in this case).
// LIBHEIF_API
int heif_image_get_bits_per_pixel_range(const struct heif_image*, enum heif_channel channel);

// LIBHEIF_API
int heif_image_has_channel(const struct heif_image*, enum heif_channel channel);

// Get a pointer to the actual pixel data.
// The 'out_stride' is returned as "bytes per line".
// When out_stride is NULL, no value will be written.
// Returns NULL if a non-existing channel was given.
// LIBHEIF_API
const uint8_t* heif_image_get_plane_readonly(const struct heif_image*,
                                             enum heif_channel channel,
                                             int* out_stride);

// LIBHEIF_API
uint8_t* heif_image_get_plane(struct heif_image*,
                              enum heif_channel channel,
                              int* out_stride);



struct heif_scaling_options;

// Currently, heif_scaling_options is not defined yet. Pass a NULL pointer.
// LIBHEIF_API
struct heif_error heif_image_scale_image(const struct heif_image* input,
                                         struct heif_image** output,
                                         int width, int height,
                                         const struct heif_scaling_options* options);

// Extends the image size to match the given size by extending the right and bottom borders.
// The border areas are filled with zero.
// LIBHEIF_API
struct heif_error heif_image_extend_to_size_fill_with_zero(struct heif_image* image,
                                                           uint32_t width, uint32_t height);

// The color profile is not attached to the image handle because we might need it
// for color space transform and encoding.
// LIBHEIF_API
struct heif_error heif_image_set_raw_color_profile(struct heif_image* image,
                                                   const char* profile_type_fourcc_string,
                                                   const void* profile_data,
                                                   const size_t profile_size);

// LIBHEIF_API
struct heif_error heif_image_set_nclx_color_profile(struct heif_image* image,
                                                    const struct heif_color_profile_nclx* color_profile);


// TO-DO: this function does not make any sense yet, since we currently cannot modify existing HEIF files.
//// LIBHEIF_API
//void heif_image_remove_color_profile(struct heif_image* image);

// Fills the image decoding warnings into the provided 'out_warnings' array.
// The size of the array has to be provided in max_output_buffer_entries.
// If max_output_buffer_entries==0, the number of decoder warnings is returned.
// The function fills the warnings into the provided buffer, starting with 'first_warning_idx'.
// It returns the number of warnings filled into the buffer.
// Note: you can iterate through all warnings by using 'max_output_buffer_entries=1' and iterate 'first_warning_idx'.
// LIBHEIF_API
int heif_image_get_decoding_warnings(struct heif_image* image,
                                     int first_warning_idx,
                                     struct heif_error* out_warnings,
                                     int max_output_buffer_entries);

// This function is only for decoder plugin implementors.
// LIBHEIF_API
void heif_image_add_decoding_warning(struct heif_image* image,
                                     struct heif_error err);

// Release heif_image.
// LIBHEIF_API
void heif_image_release(const struct heif_image*);


// Note: a value of 0 for any of these values indicates that the value is undefined.
// The unit of these values is Candelas per square meter.
struct heif_content_light_level
{
  uint16_t max_content_light_level;
  uint16_t max_pic_average_light_level;
};

// LIBHEIF_API
int heif_image_has_content_light_level(const struct heif_image*);

// LIBHEIF_API
void heif_image_get_content_light_level(const struct heif_image*, struct heif_content_light_level* out);

// Returns whether the image has 'content light level' information. If 0 is returned, the output is not filled.
// LIBHEIF_API
int heif_image_handle_get_content_light_level(const struct heif_image_handle*, struct heif_content_light_level* out);

// LIBHEIF_API
void heif_image_set_content_light_level(const struct heif_image*, const struct heif_content_light_level* in);


// Note: color coordinates are defined according to the CIE 1931 definition of x as specified in ISO 11664-1 (see also ISO 11664-3 and CIE 15).
struct heif_mastering_display_colour_volume
{
  uint16_t display_primaries_x[3];
  uint16_t display_primaries_y[3];
  uint16_t white_point_x;
  uint16_t white_point_y;
  uint32_t max_display_mastering_luminance;
  uint32_t min_display_mastering_luminance;
};

// The units for max_display_mastering_luminance and min_display_mastering_luminance is Candelas per square meter.
struct heif_decoded_mastering_display_colour_volume
{
  float display_primaries_x[3];
  float display_primaries_y[3];
  float white_point_x;
  float white_point_y;
  double max_display_mastering_luminance;
  double min_display_mastering_luminance;
};

struct heif_ambient_viewing_environment
{
  uint32_t ambient_illumination;
  uint16_t ambient_light_x;
  uint16_t ambient_light_y;
};

// LIBHEIF_API
int heif_image_has_mastering_display_colour_volume(const struct heif_image*);

// LIBHEIF_API
void heif_image_get_mastering_display_colour_volume(const struct heif_image*, struct heif_mastering_display_colour_volume* out);

// Returns whether the image has 'mastering display colour volume' information. If 0 is returned, the output is not filled.
// LIBHEIF_API
int heif_image_handle_get_mastering_display_colour_volume(const struct heif_image_handle*, struct heif_mastering_display_colour_volume* out);

// LIBHEIF_API
void heif_image_set_mastering_display_colour_volume(const struct heif_image*, const struct heif_mastering_display_colour_volume* in);


// Converts the internal numeric representation of heif_mastering_display_colour_volume to the
// normalized values, collected in heif_decoded_mastering_display_colour_volume.
// Values that are out-of-range are decoded to 0, indicating an undefined value (as specified in ISO/IEC 23008-2).
// LIBHEIF_API
struct heif_error heif_mastering_display_colour_volume_decode(const struct heif_mastering_display_colour_volume* in,
                                                              struct heif_decoded_mastering_display_colour_volume* out);

// LIBHEIF_API
void heif_image_get_pixel_aspect_ratio(const struct heif_image*, uint32_t* aspect_h, uint32_t* aspect_v);

// Returns whether the image has 'pixel aspect ratio information' information. If 0 is returned, the output is filled with the 1:1 default.
// LIBHEIF_API
int heif_image_handle_get_pixel_aspect_ratio(const struct heif_image_handle*, uint32_t* aspect_h, uint32_t* aspect_v);

// LIBHEIF_API
void heif_image_set_pixel_aspect_ratio(struct heif_image*, uint32_t aspect_h, uint32_t aspect_v);
