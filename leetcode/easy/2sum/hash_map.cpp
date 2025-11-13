class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> mapper;

        for(int i = 0;i < nums.size(); i++){
            int val = target - nums[i];
            if (mapper.count(val)){
                return {mapper[val], i};
            }
            mapper[nums[i]] = i;
        }
        return {};
    }
};