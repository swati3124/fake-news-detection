# ---- Cleanup everything before start ----
rm(list = ls())
gc()

# ---- API TO KnowledgeGraph ----
source("./experimentAPI.R")

# ---- INPUT and CONFIGURATIONS ----

EDGE_TYPE_FILE = "../data/dbpedia.edgetypes"
INPUT_FILE = "../true_data/state_capital.csv"
CLUSTER_SIZE = 48
FALSE_PER_TRUE = 5
DISCARD_REL = 191 # corresponds to the edege numbers. 191 refers to capitalOf
ASSOCIATE_REL = c(404)
max_depth = 3

# ---- Load edge type file ----

mapfile <- read.csv(EDGE_TYPE_FILE, sep="\t", header=F)
mapfile$V1 <- as.numeric(mapfile$V1)
mapfile$V2 <- as.character(mapfile$V2)

# ---- Init workers ----

cl <- makeCluster(CLUSTER_SIZE) 
clusterExport(cl = cl, varlist=c("heter_full_path", "meta_path",
                                 "connectedby", "rel_path", "truelabeled", "falselabeled", "str_split",
                                 "request","DISCARD_REL"), envir = environment())

# ---- Load input data ----
dat.true <- read.csv(INPUT_FILE)

if (ncol(dat.true) < 3)
  dat.true$label <- T

# ---- Construct false labeled data -----
set.seed(233)

dat.false <- rbind.fill(apply(dat.true, 1, function(x){
  candidates <- unique(dat.true[which(dat.true[,1] != x[1]), 2])
  candidates <- unlist(lapply(candidates, function(y){
    if(length(which(dat.true[,1] == x[1] & dat.true[,2] == y) != 0)) {
      return(NULL)
    }
    return(y)
  }))
  return(data.frame(src=x[1], 
                    dst=sample(candidates, FALSE_PER_TRUE),
                    label=F))
}))

colnames(dat.true) <- c("src","dst","label")
dat <- rbind(dat.true, dat.false)

elapsed.time <- data.frame()

## Test Method

experiment.test <- eval.test(dat, DISCARD_REL)
write.csv(experiment.test$raw, "../result/capital_state_all.test.csv", row.names=F)
print("PREDICATE PATH")
print(experiment.test$eval)

elapsed.time <- rbind(elapsed.time, data.frame(method="test", elapsed = experiment.test$elapsed[3] * CLUSTER_SIZE / nrow(dat)))

q()