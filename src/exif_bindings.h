#include <Rcpp.h>
#include <libexif/exif-data.h>
using namespace Rcpp;

#ifndef __EXIF_BINDINGS__
#define __EXIF_BINDINGS__

class exif_bindings {
  
private:
  
  std::vector < std::string > names;
  
public:
  
  /**
   * Constructor for populating names and descriptions.
   */
  exif_bindings();
  
  std::vector < std::string > get_names();
};

#endif