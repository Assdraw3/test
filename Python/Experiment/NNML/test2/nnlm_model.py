import torch
import torch.nn as nn

class NNLM(nn.Module):
    def __init__(self, vocab_size, embedding_dim, hidden_dim, window_size):
        super().__init__()
        self.embedding = nn.Embedding(vocab_size, embedding_dim)
        self.fc_hidden = nn.Linear(window_size * embedding_dim, hidden_dim)
        self.tanh = nn.Tanh()
        self.fc_output = nn.Linear(hidden_dim, vocab_size)

    def forward(self, x):
        emb = self.embedding(x)
        B = x.size(0)
        emb_flat = emb.view(B, -1)
        hidden = self.tanh(self.fc_hidden(emb_flat))
        logits = self.fc_output(hidden)
        return logits