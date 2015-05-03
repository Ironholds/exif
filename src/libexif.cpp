#include <Rcpp.h>
#include <libexif/exif-data.h>
using namespace Rcpp;

ExifData *read_file(const char *file){
  ExifData *output;
  output = exif_data_new_from_file(file);
  return output;
}

List get_exif_info(const char *file){
  
  List output;
  ExifData *read_result = read_file(file);
  if(!read_result){
    output.push_back("Could not read file");
  } else {
    
  }
  return output;
}

//'@title read EXIF data into R
//'@description \code{read_exif}
//'
//'@param filenames a vector of full filenames.
//'
//'@return A nested set of lists, containing
//'the metadata for each file. If only one file
//'is requested, the metadata will be at the "top level"
//'of the list, rather than unnecessarily nested; if
//'a file cannot be found or read correctly, the metadata
//'for that file will consist of the line "Could not read file".
//'
//'@export
//[[Rcpp::export]]
List read_exif(std::vector < std::string > filenames){
  
  List output;
  int input_size = filenames.size();
  const char * input_holding;
  
  if(input_size == 1){
    input_holding = filenames[0].c_str();
    output = get_exif_info(input_holding);
  } else {
    
  }
  return output;
}