library("e1071")

df = read.table("sample1.csv",header = TRUE,sep = ",")
df

traindata = as.data.frame(df[1:14,])
traindata
testdata = as.data.frame(df[15,])
testdata

# build model
model = naiveBayes(Enrolls ~ Age+Income+JobSatisfaction+Desire,traindata,laplace = 0.01)
model

# make the prediction
results = predict(model, newdata = testdata, type = "raw")
results

