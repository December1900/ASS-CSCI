library(arules)
library(arulesViz)

df <- read.csv("A1_success_data.csv")

itemsets<- apriori(df, parameter=list(minlen=1, maxlen=10, support=0.01, target="frequent itemsets"))

summary(itemsets)

itemsets<- apriori(df, parameter=list(minlen=1, maxlen=10, support=0.02, target="frequent itemsets"))

summary(itemsets)

itemsets<- apriori(df, parameter=list(minlen=1, maxlen=10, support=0.05, target="frequent itemsets"))

summary(itemsets)


rules<- apriori(df, parameter=list(support=0.001,confidence=0.6, target = "rules"))
plot(rules)
plot(rules@quality)

slope<- sort(round(rules@quality$lift / rules@quality$confidence, 2))
unlist(lapply(split(slope,f=slope),length))
inspect(head(sort(rules, by="lift"), 10))
inspect(head(sort(rules, by="confidence"), 10))
inspect(head(sort(rules, by="support"), 10))

confidentRules<- rules[quality(rules)$confidence > 0.9]
plot(confidentRules, method="matrix", measure=c("lift", "confidence"))

highLiftRules <- head(sort(rules, by="lift"), 5) 
plot(highLiftRules, method="graph", control=list(type="items"))

test<-inspect(sort(rules, by="lift"))
test[test$rhs=="{Success=Yes}",]
test[test$rhs=="{Success=No}",]





