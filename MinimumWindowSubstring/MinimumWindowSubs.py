class Solution:
    def minWindow(self, s: str, t: str) -> str:
        if not t or not s:
            return ""

        # Count required characters
        need = {}
        for c in t:
            need[c] = need.get(c, 0) + 1

        missing = len(t)          # how many characters are still needed
        left = 0                  # left pointer of the window
        start = 0                 # best window start
        min_len = float('inf')    # best window length

        for right, char in enumerate(s):
            # If this character helps satisfy need, reduce missing
            if char in need:
                if need[char] > 0:
                    missing -= 1
                need[char] -= 1

            # When all characters are satisfied, try shrinking window
            while missing == 0:
                window_len = right - left + 1
                if window_len < min_len:
                    min_len = window_len
                    start = left

                # Try removing s[left] from the window
                left_char = s[left]
                if left_char in need:
                    need[left_char] += 1
                    # If we now need this char, window no longer valid
                    if need[left_char] > 0:
                        missing += 1
                left += 1

        return "" if min_len == float('inf') else s[start:start + min_len]
