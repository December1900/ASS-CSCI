library("dplyr")
library("magrittr")
library("data.table")
library("tidytext")
library("topicmodels")
library("colorspace")
library("purrr")
library("ldatuning")
library("gmp")
library("RColorBrewer")
library("wordcloud")
library("ggplot2")
library("lubridate")
library("lubridate")
library("reshape2")
library("textmineR")
library("lda")

data("cora.documents")

#visualising topics of words based on the max value
set.seed(1234)
pdf("result.pdf")
for(i in 1:length(unique(final_summary_words$topic)))
{  wordcloud(words = subset(final_summary_words ,topic == i)$word, freq = subset(final_summary_words ,topic == i)$value, min.freq = 1,
             max.words=200, random.order=FALSE, rot.per=0.35, 
             colors=brewer.pal(8, "Dark2"))}

dev.off()

