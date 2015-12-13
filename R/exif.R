#' @title Read EXIF data into R
#' @name exif
#' @description exif is a package for reading EXIF media metadata into R,
#' returning it as a list in a similar fashion to jsonlite. It depends on
#' the libexif C library, which must be installed for the package to work.
#' @useDynLib exif
#' @importFrom Rcpp sourceCpp
#' @seealso \code{\link{read_exif}}
#' @docType package
#' @aliases exif exif-package
NULL

#'@title Read EXIF Metadata
#'@export
read_exif <- function(files){
  return(read_exif_(normalizePath(files, winslash = "\\", mustWork = FALSE)))
}