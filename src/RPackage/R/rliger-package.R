#' @useDynLib rliger, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export MyClass
NULL

Rcpp::loadModule("RCppLibModule", TRUE)
