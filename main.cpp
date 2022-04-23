#include "data_struct.h"

int main()
{
    std::string filePath;
    std::cout << "enter file path" << std::endl;
    std::getline(std::cin, filePath);
    DaVinci::DataStruct data(filePath);

    // test cases
    auto oc = data.OrderCounts();
    auto bbo = data.BiggestBuyOrders("DVAM2");
    auto bsat = data.BestSellAtTime("DVAM1", "15:14:00");
}
