library(Rcpp)
install.packages("ggplot2")
library(plyr)
library(cluster)
library(lattice)
library(graphics)
library(grid)
library(gridExtra)
install.packages("ggthemes")

grade_input <- as.data.frame(read.csv("grades_km_input.csv"))

kmdata_orig <- as.matrix(grade_input[,c("Student","English", "Math","Science")])
kmdata <- kmdata_orig[,2:4]
kmdata[1:10,]


wss <- numeric(15) 
for (k in 1:15) wss[k] <- sum(kmeans(kmdata, centers=k, nstart=25)$withinss)

plot(1:15, wss, type="b", xlab="Number of Clusters", ylab="Within Sum of Squares") 


km <- kmeans(kmdata,3, nstart=25)
km

c( wss[3] , sum(km$withinss) )

km <- kmeans(kmdata,3, nstart=25)
km

c( wss[3] , sum(km$withinss) )

df <- as.data.frame(kmdata_orig[,2:4])
df$cluster <- factor(km$cluster)
centers <- as.data.frame(km$centers)

g1 <- ggplot(data=df, aes(x=English, y=Math, color=cluster )) + 
  geom_point() + theme(legend.position="right") +
  geom_point(data=centers, aes(x=English,y=Math, color=as.factor(c(1,2,3))), 
             size=10, alpha=.3, show.legend =FALSE)
geom_theme

g2 <- ggplot(data=df, aes(x=English, y=Science, color=cluster )) + 
  geom_point() + 
  geom_point(data=centers, aes(x=English,y=Science, color=as.factor(c(1,2,3))), 
             size=10, alpha=.3, show_legend = FALSE)

g3 <- ggplot(data=df, aes(x=Math, y=Science, color=cluster )) + 
  geom_point() +
  geom_point(data=centers, aes(x=Math,y=Science, color=as.factor(c(1,2,3))), 
             size=10, alpha=.3, show_legend = FALSE)

tmp <- ggplot_gtable(ggplot_build(g1)) 

grid.arrange(arrangeGrob(g1 + theme(legend.position="right"),
                         g2 + theme(legend.position="right"),
                         g3 + theme(legend.position="right"),
                         top ="High School Student Cluster Analysis", ncol=1))

