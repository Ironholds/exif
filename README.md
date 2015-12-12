##urltools
A package for reading EXIF metadata into R

![downloads](http://cranlogs.r-pkg.org/badges/grand-total/urltools)

### Description
EXIF metadata provides information about the nature of a JPEG image (usually a photograph) including camera make
and model, f-stop, the ISO speed, the length of the exposure, the lens used, and the timestamp the image was taken at. The
`exif` package allows you to read this information into R. It is fully vectorised and based on compiled code.

Unfortunately it *does* require C++11, so will only work on the latest (3.1+) versions of R. You've been warned.

### Installation

While we're waiting for CRAN to approve:

    devtools::install_github("ironholds/exif")