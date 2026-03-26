#include <bits/stdc++.h>
using namespace std;

struct Customer {
    int custkey;
    int nationkey;
};

struct Orders {
    int orderkey;
    int custkey;
    string orderdate;
};

struct LineItem {
    int orderkey;
    int suppkey;
    double extendedprice;
    double discount;
};

struct Supplier {
    int suppkey;
    int nationkey;
};

struct Nation {
    int nationkey;
    int regionkey;
    string name;
};

struct Region {
    int regionkey;
    string name;
};

int main() {

    vector<Region> regions = {
        {1, "ASIA"},
        {2, "EUROPE"}
    };

    vector<Nation> nations = {
        {1, 1, "INDIA"},
        {2, 1, "CHINA"},
        {3, 2, "GERMANY"}
    };

    vector<Supplier> suppliers = {
        {1, 1},
        {2, 2},
        {3, 3}
    };

    vector<Customer> customers = {
        {1, 1},
        {2, 2},
        {3, 3}
    };

    vector<Orders> orders = {
        {1, 1, "1994-03-10"},
        {2, 2, "1994-07-21"},
        {3, 3, "1993-05-10"}
    };

    vector<LineItem> lineitems = {
        {1, 1, 1000.0, 0.1},
        {2, 2, 2000.0, 0.2},
        {3, 3, 3000.0, 0.15}
    };

    unordered_set<int> asiaRegions;
    for (auto &r : regions) {
        if (r.name == "ASIA") {
            asiaRegions.insert(r.regionkey);
        }
    }

    unordered_map<int, string> nationMap;
    for (auto &n : nations) {
        if (asiaRegions.count(n.regionkey)) {
            nationMap[n.nationkey] = n.name;
        }
    }

    unordered_map<int, int> supplierNation;
    for (auto &s : suppliers) {
        if (nationMap.count(s.nationkey)) {
            supplierNation[s.suppkey] = s.nationkey;
        }
    }

    unordered_map<int, int> orderCustomer;
    for (auto &o : orders) {
        if (o.orderdate >= "1994-01-01" && o.orderdate < "1995-01-01") {
            orderCustomer[o.orderkey] = o.custkey;
        }
    }

    unordered_map<int, int> customerNation;
    for (auto &c : customers) {
        if (nationMap.count(c.nationkey)) {
            customerNation[c.custkey] = c.nationkey;
        }
    }

    unordered_map<string, double> revenueByNation;

    for (auto &l : lineitems) {

        if (!orderCustomer.count(l.orderkey)) continue;

        int custkey = orderCustomer[l.orderkey];
        if (!customerNation.count(custkey)) continue;

        int custNation = customerNation[custkey];

        if (!supplierNation.count(l.suppkey)) continue;

        int suppNation = supplierNation[l.suppkey];

        if (custNation != suppNation) continue;

        string nationName = nationMap[custNation];

        double revenue = l.extendedprice * (1 - l.discount);

        revenueByNation[nationName] += revenue;
    }

    vector<pair<string, double>> result(revenueByNation.begin(), revenueByNation.end());

    sort(result.begin(), result.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });

    cout << "Nation-wise Revenue:\n";
    for (auto &p : result) {
        cout << p.first << " -> " << p.second << endl;
    }

    return 0;
}


