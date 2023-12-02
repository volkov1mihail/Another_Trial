class Solution(object):
    def removeDuplicates(self, nums):
        cur=1
        i=1
        stored=1
        if(len(nums)<2):return len(nums)

        while(i<len(nums)-1):
            if(stored==1):
                while(nums[i]<nums[cur-1]):
                    i+=1
                    if(i == len(nums)):return cur
                print('stored was = ',stored)
                if(nums[cur-1]==nums[i]): stored+=1
                else: stored=1
                print('stored = ',stored)

            else:
                while(nums[i]<=nums[cur-1]):
                    i+=1
                    if(i == len(nums)):return cur
                print('stored was = ',stored)
                stored=1
                print('stored = ',stored)
            print("cur = ",cur," i = ",i," (nums[cur],nums[i]) = (",nums[cur],",",nums[i],")")
            nums[cur]=nums[i]
            cur+=1
            i+=1
            print('cur = ', cur, 'i = ',i)
        if(i<len(nums) and ((nums[cur - 1] == nums[i] and stored == 1) or nums[cur-1] < nums[i])):
            print("cur = ",cur," i = ",i," (nums[cur],nums[i]) = (",nums[cur],",",nums[i],")")
            nums[cur]=nums[i]
            cur+=1
        print(nums)
        return cur

def main():
    nums = [1,1,1,2]
    print(nums)
    x = Solution()
    x.removeDuplicates(nums)


if __name__ == "__main__":
    main()