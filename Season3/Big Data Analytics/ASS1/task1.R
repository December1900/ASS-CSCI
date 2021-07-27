dataframe <- read.csv("A1_performance_test.csv")
app1 <- dataframe[dataframe$approach=="approach1",]$performance
app2 <- dataframe[dataframe$approach=="approach2",]$performance
appNo <- dataframe[dataframe$approach=="no_approach",]$performance

summary(app1)
summary(app2)
summary(appNo)

t.test(app1,appNo,var.equal = TRUE)
qt(p=0.05/2, df=379, lower.tail= FALSE)

t.test(app2,appNo,var.equal = TRUE)
qt(p=0.05/2, df=401, lower.tail= FALSE)

t.test(app1,app2,var.equal = TRUE)
qt(p=0.05/2, df=414, lower.tail= FALSE)
