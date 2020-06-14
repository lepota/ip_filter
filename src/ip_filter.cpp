#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

using IP = std::vector<int>;

auto to_int(std::vector<std::string>&& ip){
    IP result;
    for(const auto& item : ip)
        result.push_back(std::stoi(item));
    return result;
}

std::ostream& operator<<(std::ostream& stream, const IP& ip){
    for(auto i = 0u; i < ip.size(); ++i){
        stream << ip.at(i);
        if(i != ip.size() - 1) stream << '.';
    }
    return stream;
}

using IP_POOL = std::vector<IP>;

std::ostream& operator << (std::ostream& stream, const IP_POOL& ip_pool){
    for(const auto& ip : ip_pool)
        stream << ip << '\n';
    return stream;
}


IP ip_address(){
    return IP(0);
}

template<typename T, typename ... Args>
auto ip_address(T number, Args ... args){
    IP result = ip_address(args...);
    result.push_back(number);
    std::reverse(result.begin(), result.end());
    return result;
}

void ip_filter(const IP_POOL& ip_pool, const IP& ip){
    std::for_each(
        ip_pool.begin(),
        ip_pool.end(),
        [=](auto a) {
            int i = 0;
            for(auto item : ip)
                if (item != a.at(i)) return;
                else ++i;
            std::cout << a << '\n';
        }
    );
}

void ip_filter_any(const IP_POOL& ip_pool, int number){
    std::for_each(
        ip_pool.begin(),
        ip_pool.end(),
        [=](auto a){
            for(auto item : a)
                if (item == number){
                    std::cout << a << '\n';
                    return;
                }
        }
    );
}

int main(/*int argc, char const *argv[]*/)
{
    try
    {
        std::vector<IP> ip_pool;

        for(std::string line; std::getline(std::cin, line);){
            auto v = split(line, '\t');
            ip_pool.push_back(to_int(split(v.at(0), '.')));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](auto a, auto b) { return (a > b); });

        std::cout << ip_pool;
        // for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        //     for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        //     {
        //         if (ip_part != ip->cbegin())
        //         {
        //             std::cout << ".";

        //         }
        //         std::cout << *ip_part;
        //     }
        //     std::cout << std::endl;
        // }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        ip_filter(ip_pool, ip_address(1));
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        ip_filter(ip_pool, ip_address(46, 70));

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        ip_filter_any(ip_pool, 46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
