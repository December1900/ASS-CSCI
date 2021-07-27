library("ggplot2")
library("reshape2")
library("lda")

data(cora.documents)
data(cora.vocab)

theme_set(theme_bw())

K <- 10

N <- 9

result <- lda.collapsed.gibbs.sampler(cora.documents,
                                      K,
                                      cora.vocab,
                                      25,
                                      0.1,
                                      0.1,
                                      compute.log.likelihood=TRUE)


top.words <- top.topic.words(result$topics, 5, by.score=TRUE)

topic.props <- t(result$document_sums) / colSums(result$document_sums)

document.samples <- sample(1:dim(topic.props)[1], N)

topic.props <- topic.props[document.samples,]

topic.props[is.na(topic.props)] <- 1 / K

colnames(topic.props) <- apply(top.words, 2, paste, collapse=" ")

topic.props.df <- melt(cbind(data.frame(topic.props),document=factor(1:N)), variable.name="topic",id.vars = "document")

qplot(topic, value*100, fill=topic, stat="identity", ylab="proportion (%)", data=topic.props.df, geom="col") +
  theme(axis.text.x = element_text(angle=0, hjust=1, size=12)) + coord_flip() +
  facet_wrap(~ document, ncol=3)





