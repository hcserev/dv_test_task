# Da Vinci test task

It's a console application. After launch you need to enter in command line the file path to the *.dat file.

# Assumptions
-If in *.dat file will be incorrect data for volume or price the program will be closed
-If in function BestSellAtTime() will be incorrect data for timestamp the program will be closed

# Structure
There are 3 member functions of the class "DataStruct":
OrderCounts() returns unordered_map, where key = symbol, and value = counter
BiggestBuyOrders() returns sorted std::vector of DataNode (structure which stores timestamp, symbol, order-id, operation, side, volume and price). Size of this vector will be from 0 to 3.
BestSellAtTime() returns std::pair of price and related volume. In case of incorrect data it returns {-1.0, 0}; Negative value of price means that the result is incorrect. 
For BestSellAtTime() correctness I assume that the data in *.dat file sorted by timestamp. So I use the BinarySearchFirstStamp() function for this parameter.

