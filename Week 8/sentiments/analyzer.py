import nltk


class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        # store positive and negative words
        # from files, stripping newlines
        # and ignoring blanklines
        self.pos = [line.rstrip('\n') for line in open(positives)
                    if line.rstrip('\n')]
        self.neg = [line.rstrip('\n') for line in open(negatives)
                    if line.rstrip('\n')]

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # tokenize text
        tokens = nltk.tokenize.TweetTokenizer.tokenize(text)

        # make a list of integers, where
        # 1 is a positive word, -1 is a
        # negative word, and 0 is neutral
        analysis = []
        for word in tokens:
            if word in self.pos:
                analysis.append(1)
            elif word in self.neg:
                analysis.append(-1)
            else:
                analysis.append(0)

        # sum the list's values for sentiment analysis
        return(sum(analysis))
