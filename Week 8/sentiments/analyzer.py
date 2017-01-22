from nltk import word_tokenize


class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        self.pos = [line.rstrip('\n') for line in open(positives)]
        self.neg = [line.rstrip('\n') for line in open(negatives)]

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        tokenized_text = word_tokenize(text)
        analysis = []
        for word in tokenized_text:
            if word in self.pos:
                analysis.append(1)
            elif word in self.neg:
                analysis.append(-1)
            else:
                analysis.append(0)
        return(sum(analysis))
