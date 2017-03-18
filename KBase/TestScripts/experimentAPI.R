list.of.packages <- c("utils", "plyr", "LiblineaR", "parallel", "RWeka")
new.packages <- list.of.packages[!(list.of.packages %in% installed.packages()[,"Package"])]
if(length(new.packages)) install.packages(new.packages, repos="http://cran.rstudio.com/")

library(methods)
library(utils)
library(plyr)
library(LiblineaR)
library(parallel)
library(RWeka)

source("./knowledgeGraph.R")

## All input dfs must have at least three columns, first two columns are ids and the third column is class label.

eval.df <- function(df) {
  res <- list()
  res[["raw"]] <- df
  res[["model"]] <- Logistic(label~.,res[["raw"]])
  res[["eval"]] <- evaluate_Weka_classifier(res[["model"]], numFolds = 10, complexity = T, class = T, seed = 233)
  return(res)
}

## Basic experiment helper
eval.helper <- function(df, discard_rel, gen_func) {
  res <- list()
  ptm <- proc.time()
  res[["raw"]] <- gen_func(df, discard_rel)
  # write.csv(colnames(res[["raw"]]), "/data/bshi/dbpedia/gngm_celf.fullpath.csv")
  res[["elapsed"]] <- proc.time() - ptm
  res[["model"]] <- Logistic(label~.,res[["raw"]])
  res[["eval"]] <- evaluate_Weka_classifier(res[["model"]], numFolds = 10, complexity = T, class = T, seed = 233)
  return(res)
}

## Test method
eval.test <- function(df, discard_rel, max_depth = 3) {
  func.test <- function(df, discard_rel) {
    tmp.paths <- rbind.fill(parApply(cl, dat, 1, function(x) {
      tmp_paths <- rel_path(as.numeric(x[1]), as.numeric(x[2]), max_depth, F, DISCARD_REL)
      if(length(tmp_paths) == 0) {
        return(data.frame(label = as.logical(x[3])))
      }
      rtn <- as.data.frame(t(tmp_paths$Freq))
      colnames(rtn) <- tmp_paths$paths
      rtn <- cbind(label = as.logical(x[3]), rtn)
      return(rtn)
    }))
    tmp.paths[is.na(tmp.paths)] <- 0
    return(tmp.paths)
  }
  return(eval.helper(df, discard_rel, func.test))
}
