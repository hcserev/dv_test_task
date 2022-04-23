#ifndef  DAVINCI_DATASTRUCT_H
#define  DAVINCI_DATASTRUCT_H

#include <iostream>     // std::cout
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>      // std::ifstream
#include <sstream>

namespace DaVinci
{
    struct DataNode
    {
    private:
        std::string time;
        std::string symbol;
        std::string orderId;
        std::string side;
        char operation = ' ';
        unsigned int volume = 0;
        double price = 0.;
    public:
        void setTime(std::string iTime)
        {
            time = iTime;
        };
        std::string getTime() const
        {
            return time;
        };
        void setSymbol(std::string iSymbol)
        {
            symbol = iSymbol;
        };
        std::string getSymbol() const
        {
            return symbol;
        };
        void setOrderId(std::string iOrderId)
        {
            orderId = iOrderId;
        };
        std::string getOrderId() const
        {
            return orderId;
        };
        void setOperation(std::string iOperation)
        {
            operation = iOperation[ 0 ];
        };
        char getOperation() const
        {
            return operation;
        };
        void setSide(std::string iSide)
        {
            side = iSide;
        };
        std::string getSide() const
        {
            return side;
        };
        void setVolume(std::string iVolume)
        {
            try
            {
                volume = std::stoi(iVolume);
            }
            catch (...)
            {
                std::cout << "Error: Can't read volume value for the order-id: " << orderId;
                std::terminate();
            }
        };
        unsigned int getVolume() const
        {
            return volume;
        };
        void setPrice(std::string iPrice)
        {
            try
            {
                price = std::stod(iPrice.c_str());
            }
            catch (...)
            {
                std::cout << "Error: Can't read price value for the order-id: " << orderId;
                std::terminate();
            }
        };
        double getPrice() const
        {
            return price;
        };
    };

    class DataStruct
    {
    public:
        DataStruct(std::string fileName = "");
        DataStruct(const DataStruct& copy) = delete;
        DataStruct(DataStruct&& copy) = delete;
        DataStruct& operator=(const DataStruct& other) = delete;
        DataStruct& operator=(DataStruct&& other) noexcept = delete;

        // return unordered_map (key = symbol, value = total count)
        std::unordered_map<std::string, unsigned int> OrderCounts();

        // return std::vector of data nodes with maximum size == 3
        std::vector<DataNode> BiggestBuyOrders(std::string symbol = "DVAM1");

        // return std::pair of the best SELL price and related order volume
        // if there are no convinient SELL operations return {-1.0, 0}
        std::pair<double, double> BestSellAtTime(std::string symbol = "DVAM1", std::string timestamp = "00:00:00");

    private:
        // check timestamp correctness
        bool CheckTimeStamp(std::string timestamp);

        // binary search (O(logN)) by timestamp is possible because in the input file all lines ordered by time
        int BinarySearchFirstStamp(std::string timestamp);

        std::vector<DataNode> data;
    };
}

#endif // ! DAVINCI_DATASTRUCT_H
