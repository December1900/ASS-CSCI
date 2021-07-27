sales <- read.csv("yearly_sales.csv")

head(sales)
summary(sales)

plot(sales$num_of_orders, sales$sales_total, main="Number of Orders vs. Sales")

# perform a statistical analysis (fit a linear regression model)
results <- lm(sales$sales_total ~ sales$num_of_orders)
results
summary(results)
hist(results$residuals, breaks = 800)


