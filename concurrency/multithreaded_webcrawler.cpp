#include <iostream>
#include <string>

class Solution {
    public:
        vector<string> crawl(string startUrl, HtmlParser htmlParser){
            // Intialize the queue
            queue<string> q{{startUrl}};
            unordered_set<string> seen{{startUrl}};
            string hostname = getHostname(startUrl);

            vector<thread> threads;
            mutex mtx;
            condition_variable cond;

            auto worker = [&](){
                while(true){
                    unique_lock<mutex> lock(mtx);
                    // Worker waits for 30 seconds for condition to be true
                    cv.wait_for(lock, 30ms, [&]() { return q.size(); });

                    if (q.empty())
                        return;
                    }

                    auto url = q.front(); q.pop();
                    auto urls = htmlParser.getUrls(url);
                    lock.unlock();

                    for (const auto& url : urls) {
                        if (url.find(hostname) != string::npos) {
                            lock_guard<mutex> lock(mtx);
                            if (seen.insert(url).second)
                                q.push(url);
                        }
                    }
                    lock.lock();
                    cv.notify_all();
            }

            for (int i = 0; i < thread::hardware_concurrency(); ++i)
                    threads.emplace_back(worker);

            for (auto& t : threads) t.join();

            return {seen.begin(), seen.end()};

        }
    private:
        string getHostName(const string &url){
            return url.substr(0, url.find('/', 7));
        }
}