df <- read.csv("income.csv")

head(df)

# Income =  7.26299 + 0.99520 * Age + 1.75788 * Education - 0.93433 * Gender
modelA <- lm(Income ~ Age + Education + Gender, data=df)
summary(modelA)

# Income = 6.75822 + 0.99603 * Age + 1.75860 * Education
modelB <- lm(Income ~ Age + Education, data=df)
summary(modelB)

item <- data.frame(Age=41, Education=12)

# make prediction
prediction <- predict(modelB, item)
prediction

# compute the confidence interval 
ci <- predict(modelB, item, interval = "confidence")
ci

# compute the prediction interval
pi <- predict(modelB, item, interval = "prediction")
pi
