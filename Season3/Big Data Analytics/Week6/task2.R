library(pROC)
df <- read.csv("churn.csv")

head(df)

modelA <- lm(Churned ~ Age + Married + Cust_years + Churned_contacts, data = df)

summary(modelA)

modelB <- lm(Churned ~ Age + Married + Churned_contacts, data = df)

summary(modelB)

modelC <- lm(Churned ~ Age + Churned_contacts, data = df)

summary(modelC)

pre <- predict(modelC, type='response')

# draw ROC
modelCroc <- roc(df$Churned, pre)

plot(modelCroc, print.auc=TRUE, auc.polygon=TRUE, grid=c(0.1, 0.2),
     grid.col=c("blue", "red"), max.auc.polygon=TRUE,
     auc.polygon.col="skyblue", print.thres=TRUE)

# put the predicted probability prob and the actual result y in a data frame
data <- data.frame(prob=pre, obs=df$Churned)

# sort by predicted probability from low to high
data <- data[order(data$prob),]
n <- nrow(data)
tpr <- fpr <- rep(0,n)

# calculate TPR and FPR according to different thresholds
for (i in 1:n) {
  threshold <- data$prob[i]
  tp <- sum(data$prob > threshold & data$obs == 1)
  fp <- sum(data$prob > threshold & data$obs == 0)
  tn <- sum(data$prob < threshold & data$obs == 0)
  fn <- sum(data$prob < threshold & data$obs == 1)
  tpr[i] <- tp/(tp+fn) 
  fpr[i] <- fp/(tn+fp)
}
plot(fpr,tpr,type='l')
abline(a=0,b=1)



