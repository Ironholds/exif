#include <Rcpp.h>
#include "exif.h"
using namespace Rcpp;

easyexif::EXIFInfo read_exif_single(std::string file){
  
  // Open file, throwing an error if we can't.
  const char* filename_pointer = file.c_str();
  FILE *file_pointer = fopen(filename_pointer, "rb");
  if(!file_pointer){
    throw std::range_error("Can't open file: " + file);
  }
  
  // Read information into a buffer
  fseek(file_pointer, 0, SEEK_END);
  unsigned long fsize = ftell(file_pointer);
  rewind(file_pointer);
  unsigned char *buf = new unsigned char[fsize];
  if (fread(buf, 1, fsize, file_pointer) != fsize) {
    delete[] buf;
    throw std::range_error("Can't read information from file: " + file);
  }
  fclose(file_pointer);
  
  // Parse EXIF
  easyexif::EXIFInfo result;
  int code = result.parseFrom(buf, fsize);
  delete[] buf;
  if(code){
    throw std::range_error("Can't parse information in file: " + file);
  }
  
  // Return
  return result;
}

//[[Rcpp::export]]
DataFrame read_exif(std::vector < std::string > files){
  
  // Output cols. This is gonna be ~~ugly~~
  unsigned int input_size = files.size();
  std::vector < std::string > makes(input_size);
  std::vector < std::string > models(input_size);
  std::vector < std::string > software(input_size);
  std::vector < int > bits(input_size);
  std::vector < int > image_width(input_size);
  std::vector < int > image_height(input_size);
  std::vector < std::string > descriptions(input_size);
  std::vector < int > orientations(input_size);
  std::vector < std::string > copyright(input_size);
  std::vector < std::string > dt(input_size);
  std::vector < std::string > dt_origin(input_size);
  std::vector < std::string > dt_digit(input_size);
  std::vector < std::string > subsecond(input_size);
  std::vector < double > exposure_time(input_size);
  std::vector < double > f_stop(input_size);
  std::vector < int > iso_speed(input_size);
  std::vector < double > subject_dist(input_size);
  std::vector < double > exposure_bias(input_size);
  std::vector < bool > flash(input_size);
  std::vector < int > metering(input_size);
  std::vector < double > focal_length(input_size);
  std::vector < int > focal_length_35mm(input_size);
  std::vector < double > latitude(input_size);
  std::vector < double > longitude(input_size);
  std::vector < double > altitude(input_size);
  std::vector < double > lens_min_focal_length(input_size);
  std::vector < double > lens_max_focal_length(input_size);
  std::vector < double > lens_min_f_stop(input_size);
  std::vector < double > lens_max_f_stop(input_size);
  std::vector < std::string > lens_make(input_size);
  std::vector < std::string > lens_model(input_size);
  
  for(unsigned int i = 0; i < input_size; i++){
    
    // Retrieve data
    easyexif::EXIFInfo result = read_exif_single(files[i]);
    
    // Pass values through
    makes[i] = result.Make;
    models[i] = result.Model;
    software[i] = result.Software;
    bits[i] = result.BitsPerSample;
    image_width[i] = result.ImageWidth;
    image_height[i] = result.ImageHeight;
    descriptions[i] = result.ImageDescription;
    orientations[i] = result.Orientation;
    copyright[i] = result.Copyright;
    dt[i] = result.DateTime;
    dt_origin[i] = result.DateTimeOriginal;
    dt_digit[i] = result.DateTimeDigitized;
    subsecond[i] = result.SubSecTimeOriginal;
    exposure_time[i] = (1.0/result.ExposureTime);
    f_stop[i] = result.FNumber;
    iso_speed[i] = result.ISOSpeedRatings;
    subject_dist[i] = result.SubjectDistance;
    exposure_bias[i] = result.ExposureBiasValue;
    flash[i] = ((int)result.Flash != 0);
    metering[i] = result.MeteringMode;
    focal_length[i] = result.FocalLength;
    focal_length_35mm[i] = result.FocalLengthIn35mm;
    latitude[i] =  result.GeoLocation.Latitude;
    longitude[i] = result.GeoLocation.Longitude;
    altitude[i] = result.GeoLocation.Altitude;
    lens_min_focal_length[i] = result.LensInfo.FocalLengthMin;
    lens_max_focal_length[i] = result.LensInfo.FocalLengthMax;
    lens_min_f_stop[i] = result.LensInfo.FStopMin;
    lens_max_f_stop[i] = result.LensInfo.FStopMax;
    lens_make[i] = result.LensInfo.Make;
    lens_model[i] = result.LensInfo.Model;
  }
  
  // Create and return output
  List output;
  
  output["make"] = makes; output["model"] = models;
  output["software"] = software; output["bits_per_sample"] = bits;
  output["image_width"] = image_width; output["image_height"] = image_height;
  output["description"] = descriptions; output["orientation"] = orientations;
  output["copyright"] = copyright; output["timestamp"] = dt;
  output["origin_timestamp"] = dt_origin; output["digitised_timestamp"] = dt_digit;
  output["subsecond_timestamp"] = subsecond; output["exposure_time"] = exposure_time;
  output["f_stop"] = f_stop; output["iso_speed"] = iso_speed;
  output["subject_distance"] = copyright; output["exposure_bias"] = exposure_bias;
  output["used_flash"] = flash; output["metering"] = metering;
  output["focal_length"] = focal_length; output["focal_length_35mm"] = focal_length_35mm;
  output["latitude"] = latitude; output["longitude"] = longitude;
  output["altitude"] = altitude; output["lens_min_focal_length"] = lens_min_focal_length;
  output["lens_max_focal_length"] = lens_max_focal_length; output["lens_min_f_stop"] = lens_min_f_stop;
  output["lens_max_f_stop"] = lens_max_f_stop; output["lens_make"] = lens_make;
  output["lens_model"] = lens_model;
  output.attr("class") = "data.frame";
  output.attr("row.names") = seq(1, input_size);
  return output;
}