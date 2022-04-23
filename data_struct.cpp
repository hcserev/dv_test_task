#include "data_struct.h"

DaVinci::DataStruct::DataStruct(std::string fileName)
{
    std::string line;
    std::string token;
    std::ifstream file(fileName);

    std::string prevTime = "";
    int fieldNum = 0;
    while (getline(file, line, '\n'))
    {
        DaVinci::DataNode currentLineData;
        std::stringstream ss(line);
        while (getline(ss, token, ';'))
        {
            switch (fieldNum)
            {
            case 0: currentLineData.setTime(token);       break;
            case 1: currentLineData.setSymbol(token);     break;
            case 2: currentLineData.setOrderId(token);    break;
            case 3: currentLineData.setOperation(token);  break;
            case 4: currentLineData.setSide(token);       break;
            case 5: currentLineData.setVolume(token);     break;
            case 6: currentLineData.setPrice(token);      break;
            default: break;
            }
            fieldNum++;
        }

        try 
        {
            data.push_back(std::move(currentLineData));
        }
        catch (...)
        {
            std::cout << "Error: Allocate problem for vector";
            std::terminate();
        }
        fieldNum = 0;
    }
};

std::unordered_map<std::string, unsigned int> DaVinci::DataStruct::OrderCounts()
{
    std::unordered_set<std::string> setSymbPlusID;
    for (const auto& it : data)
    {
        setSymbPlusID.insert(it.getSymbol() + "*" + it.getOrderId());
    }

    std::unordered_map<std::string, unsigned int> counter;
    for (const auto& it : setSymbPlusID)
    {
        int findSeparator = it.find("*");
        if (findSeparator != std::string::npos)
            counter[it.substr(0, findSeparator)]++;
    }

    return counter;
};

std::vector<DaVinci::DataNode> DaVinci::DataStruct::BiggestBuyOrders(std::string symbol)
{
    const int biggestOrdersNum = 3;
    // if we are looking for a fixed number (in this case number == 3) of orders
    // we may use O(N)-time and O(1)-size complexity algorithm

    std::vector<DaVinci::DataNode> biggestOrders;

    for (const auto& it : data)
    {
        if (it.getSymbol() == symbol && it.getSide() == "BUY" && (it.getOperation() == 'I' || it.getOperation() == 'A'))
        {
            if (biggestOrders.size() < biggestOrdersNum)
            {
                bool needToAddNewOrder = true;
                for (size_t i = 0; i < biggestOrders.size(); i++)
                {
                    if (biggestOrders[i].getOrderId() == it.getOrderId())
                    {
                        if (it.getPrice() * it.getVolume() > biggestOrders[i].getPrice() * biggestOrders[i].getVolume())
                            biggestOrders[i] = it;
                        needToAddNewOrder = false;
                        break;
                    }
                }
                if (needToAddNewOrder)
                    biggestOrders.push_back(it);
            }
            else
            {
                bool needToAddNewOrder = true;
                for (size_t i = 0; i < biggestOrders.size(); i++)
                {
                    if (biggestOrders[i].getOrderId() == it.getOrderId())
                    {
                        if (it.getPrice() * it.getVolume() > biggestOrders[i].getPrice() * biggestOrders[i].getVolume())
                            biggestOrders[i] = it;
                        needToAddNewOrder = false;
                        break;
                    }
                }
                if (needToAddNewOrder && biggestOrders.back().getVolume() * biggestOrders.back().getPrice() < it.getVolume() * it.getPrice())
                    biggestOrders.back() = it;
            }

            // as biggestOrdersNum is fixed, this sort has O(1)-time complexity
            std::sort(biggestOrders.begin(), biggestOrders.end(), [](auto first, auto second) {
                return first.getVolume() * first.getPrice() > second.getVolume() * second.getPrice(); });
        }
    }

    return biggestOrders;
}

std::pair<double, double> DaVinci::DataStruct::BestSellAtTime(std::string symbol, std::string timestamp)
{
    if (!CheckTimeStamp(timestamp))
    {
        std::cout << "Error: Timestamp is incorrect";
        std::terminate();
    }

    std::pair<double, unsigned int> res = {-1.0, 0};

    int index = BinarySearchFirstStamp(timestamp);
    while (index < data.size() && data[index].getTime().substr(0, timestamp.size()) == timestamp)
    {
        if (data[index].getSide() == "SELL" && data[index].getPrice() > res.first)
        {
            res.first = data[index].getPrice();
            res.second = data[index].getVolume();
        }
        index++;
        if (index == data.size())
            break;
    }

    return res;
}

bool DaVinci::DataStruct::CheckTimeStamp(std::string timestamp)
{
    auto isDigit = [](char symb)
    {
        return (symb >= '0' && symb <= '9');
    };
    auto toNum = [](char symb1, char symb2)
    {
        return (symb1 - '0') * 10 + (symb2 - '0');
    };
    // assume timestamp format is HH::MM::SS
    if (timestamp.size() == 8)
    {
        if (isDigit(timestamp[0]) && isDigit(timestamp[1]) &&
            isDigit(timestamp[3]) && isDigit(timestamp[4]) &&
            isDigit(timestamp[6]) && isDigit(timestamp[6]))
        {
            if (toNum(timestamp[0], timestamp[1]) >= 24) return false; // check hours correctness
            if (toNum(timestamp[3], timestamp[4]) >= 60) return false; // check minutes correctness
            if (toNum(timestamp[6], timestamp[7]) >= 60) return false; // check seconds correctness
        }
        else
            return false;
    }
    return true;
};

int DaVinci::DataStruct::BinarySearchFirstStamp(std::string timestamp)
{
    size_t timestampSize = timestamp.size();
    int start = 0;
    int end = data.size() - 1;
    int mid;

    while (start <= end)
    {
        mid = start + (end - start) / 2;
        if (data[mid].getTime().substr(0, timestampSize) > timestamp)
            end = mid - 1;
        else if (data[mid].getTime().substr(0, timestampSize) < timestamp)
            start = mid + 1;
        else
            return mid;
    }
    return start + (end - start) / 2;
}