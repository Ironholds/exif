% Generated by roxygen2 (4.1.1): do not edit by hand
% Please edit documentation in R/exif.R
\name{read_exif}
\alias{read_exif}
\title{Read EXIF Metadata}
\usage{
read_exif(files)
}
\arguments{
\item{files}{a vector of files to read in.}
}
\value{
a data.frame, with each row consisting of the metadata for one file in \code{files}. Absent values are
represented by an empty string for character columns, and 0 for numeric columns.
}
\description{
\code{read_exif} reads EXIF metadata from JPEG files,
returning it as a data.frame.
}
\examples{
# A simple example using included images
file <- system.file("extdata/dog_test_img.jpg", package="exif")
file_metadata <- read_exif(file)
}

