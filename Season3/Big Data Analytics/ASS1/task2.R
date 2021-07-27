library(plyr)
#install.packages('ggplot2')
#install.packages('colorspace')
library(ggplot2)
library(cluster)
library(lattice)
library(graphics)
library(grid) 
library(gridExtra)

raw_input = as.data.frame(iris)
kmdata_org = as.matrix(raw_input[,c("Sepal.Length","Sepal.Width","Petal.Length","Petal.Width","Species")])
summary(raw_input)

colors <-c("red","green","blue")
pairs(iris[1:4],pch=21,bg=colors[unclass(iris$Species)])

par(xpd=TRUE)
legend(0.2,0.02,horiz=TRUE,as.vector(unique(iris$Species)),fill=colors,bty="n")

kmdata <- kmdata_org[,1:4]

wss <- numeric(15)
for (k in 1:15) 
  wss[k] <- sum(kmeans(kmdata, centers=k,nstart=25)$withinss)
plot(1:15, wss, type="b", xlab="Number of Clusters", ylab="Within Sum of Squares")

km = kmeans(kmdata, 3)
km
str(km)
table(iris$Species,km$cluster)

df = as.data.frame(kmdata[,1:4])
df$cluster = factor(km$cluster)
centers = as.data.frame(km$centers)

fig1 = ggplot(data=df, aes(x=Sepal.Length, y=Petal.Length, color=cluster ))+geom_point() + geom_point(data=centers,aes(x=Sepal.Length,y=Petal.Length, color=as.factor(c(1,2,3))),size=10, alpha=.3, show.legend = FALSE)
fig2 = ggplot(data=df, aes(x=Sepal.Length, y=Sepal.Width, color=cluster ))+geom_point() + geom_point(data=centers,aes(x=Sepal.Length, y=Sepal.Width, color=as.factor(c(1,2,3))),size=10, alpha=.3, show.legend = FALSE)
fig3 = ggplot(data=df, aes(x=Sepal.Length, y=Petal.Width, color=cluster ))+geom_point() + geom_point(data=centers,aes(x=Sepal.Length,y=Petal.Width, color=as.factor(c(1,2,3))),size=10, alpha=.3, show.legend = FALSE)
fig4 = ggplot(data=df, aes(x=Sepal.Width, y=Petal.Length, color=cluster ))+geom_point() + geom_point(data=centers,aes(x=Sepal.Width,y=Petal.Length, color=as.factor(c(1,2,3))),size=10, alpha=.3, show.legend = FALSE)
fig5 = ggplot(data=df, aes(x=Sepal.Width, y=Petal.Width, color=cluster ))+geom_point() + geom_point(data=centers,aes(x=Sepal.Width,y=Petal.Width, color=as.factor(c(1,2,3))),size=10, alpha=.3, show.legend =  FALSE)
fig6 = ggplot(data=df, aes(x=Sepal.Width, y=Sepal.Length, color=cluster ))+geom_point() + geom_point(data=centers,aes(x=Sepal.Width,y=Sepal.Length, color=as.factor(c(1,2,3))),size=10, alpha=.3, show.legend = FALSE)
grid.arrange(arrangeGrob(fig1 + theme(legend.position = "none"),
                         fig2 + theme(legend.position = "none"),
                         fig3 + theme(legend.position = "none"),
                         fig4 + theme(legend.position = "none"),
                         fig5 + theme(legend.position = "none"),
                         fig6 + theme(legend.position = "none"),
                         ncol = 2))

idx <- sample(1:dim(iris)[1],100)
irisSP <- iris[idx,]
irisSP$Species <- NULL

hc <- hclust(dist(irisSP),method = "ave")
plot(hc, hang= -1, labels = iris$Species[idx])

rect.hclust(hc, k=3)
groups <- cutree(hc, k=3)


