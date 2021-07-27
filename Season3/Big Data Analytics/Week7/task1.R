library("rpart")
library("rpart.plot")

dtrain = read.table("DTdata.csv",header = TRUE,sep=",")
dtrain

# make a simple decision tree
fit = rpart(Play ~ Outlook + Temperature + Humidity + Wind,method = "class",
            data = dtrain,
            control = rpart.control(minsplit = 1),
            parms = list(split='information'))

summary(fit)

# plot the tree
rpart.plot(fit,type=4,extra=1)

# create the new observation
obs = data.frame(Outlook="rainy",Temperature="hot",Humidity="high",Wind=TRUE)

#prediction outcome for a new observation
predict(fit,obs=obs,type="prob")
