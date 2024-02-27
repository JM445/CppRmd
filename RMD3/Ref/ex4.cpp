#include <string>
#include <map>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

using vertex_t = std::string;
using weight_t = float;
using nbh_t = std::pair<vertex_t, weight_t>;
using Graph = std::map<vertex_t, std::vector<nbh_t>>;

template <class T, class Proj>
class PrioryQueue
{
    Proj            m_proj;
    std::vector<T>  m_heap;

    public:
        PrioryQueue(Proj proj) : m_proj(proj) {            
        } 

        bool empty() const {
            return m_heap.empty();
        }

        void push(T v) {
            m_heap.push_back(v);
        }

        T    pop() {
            auto pos = std::ranges::min_element(m_heap, std::less<>{}, m_proj);
            auto tmp = std::exchange(*pos, std::move(m_heap.back()));
            m_heap.pop_back();
            return tmp;
        }
};


auto shortest_path(const Graph& g, vertex_t src) -> std::map<vertex_t, weight_t>
{
    std::map<vertex_t, weight_t> distances;
    auto proj = [&distances](vertex_t x) { return distances[x]; };
    auto queue = PrioryQueue<vertex_t, decltype(proj)>(proj);

    distances[src] = 0;
    queue.push(src);

    while (!queue.empty())
    {
        auto p = queue.pop();
        weight_t d = distances[p];
        for (auto [q, wq] : g.at(p)) {
            weight_t new_distance = d + wq;
            auto [qv, isnew] = distances.emplace(q, new_distance);
            weight_t& distance = qv->second;
            if (isnew) {
                queue.push(q);   
            } else {
                distance = std::min(new_distance, distance);
            }
        }
    }

    return distances;
}


int main()
{
    Graph g;
    g["A"] = {{"B", 7}, {"C", 9}};
    g["B"] = {{"A", 7}, {"D", 3}};
    g["C"] = {{"A", 9}, {"D", 5}};
    g["D"] = {{"B", 3}, {"C", 5}, {"E", 7}, {"F", 4}, {"G", 2}};
    g["E"] = {{"D", 7}, {"F", 2}};
    g["F"] = {{"D", 4}, {"E", 2}, {"G", 1}};
    g["G"] = {{"D", 2}, {"F", 1}};

    auto res = shortest_path(g, "A");

    for (auto [k,v] : res)
        std::cout << k << " : " << v << "\n";


}