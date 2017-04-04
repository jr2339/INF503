class SuffixTrie(object):
    def __init__(self,t):
        # make suffix trie from t, t means terminal

        t += '$' #special terminator symbol

        self.root = {}

        for i in xrange(len(t)): # for each suffix
            current = self.root
            for c in t[i:]: # for each character in ith suffix
                if c not in current:
                    current[c] = {} # add outgoing edage if necessary
                current = current[c]

    def followPath(self,s):
        """Follow path given by characters of s. Return node at the
           end of path, or None if we fall off."""
        current = self.root
        for c in s:
            if c not in current:
                return None
            current = current[c]
        return current

    def hashSubstring(self, s):
        """
           Return true if s appears as a substring of t
        """
        return self.followPath(s) is not None
    def hashSuffix(self,s):
        """
        Return true if s is a suffix of t
        """
        node = self.followPath(s)
        return node is not None and '$' in node
