sales <- read.csv("yearly_sales.csv")

sales$per_order <- sales$sales_total/sales$num_of_orders

write.table(sales, "sales_modified.txt", sep="\t", row.names = FALSE)

jpeg(file="sales_hist.jpeg")

hist(sales$num_of_orders)

dev.off()

getwd()

list.files()

View(sales)

ls()

rm(sales)

rm(list=ls())

