#include "exif_bindings.h"

exif_bindings::exif_bindings(){
  ExifTag tag;
  int tag_length = exif_tag_table_count();
  const char * holding;
  std::vector < std::string > names_(tag_length);

  for(int i = 0; i < tag_length; i++){
    tag = exif_tag_table_get_tag(i);
    holding = exif_tag_get_title(tag);
    if(!holding){
      names_[i] = "";
    } else {
      names_[i] = std::string(holding);
    }
  }
  names = names_;
}

std::vector < std::string > exif_bindings::get_names(){
  return names;
}