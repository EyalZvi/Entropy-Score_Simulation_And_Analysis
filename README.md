# Entropy Score Simulation And Analysis
**This project is an implementation of the Entropy-Score method**: Detection of DDOS attacks and Flash Crowd and differentiating between them

Although there are plenty of different techniques designed to detect DDOS attacks, they all have their limitations, one of which is the inability to differentiate between Flash Crowd and DDOS attacks.

Flash crowd is an unexpected surge in visitors to a website, usually because of some newsworthy event.

Differentiating between DDoS and Flash Crowd is crucial do to the fact that filtering Flash Crowd can lead to loss of business or credibility.

The article we chose to implement proposes a new technique to detect DDOS attacks and differentiate them from Flash Crowd: **Entropy – Score**
First, the packets are characterized using an entropy-based method.
Then, by using a score-based method the malicious packets are filtered and differentiated from the Flash Crowd ones.

As we can see from our results of 89% decision correctness, we can very efficiently differentiate between DDOS attacks Flash Crowd, also, normal traffic is never mistaken for both.
As seen in our results, the algorithm has an extremely low False – Positive rate, 0% in our simulation.

![image](https://user-images.githubusercontent.com/92316457/185896268-f2a0c240-63cc-48d7-a7ce-9b02d1233aa9.png)

![image](https://user-images.githubusercontent.com/92316457/185896298-59432970-8349-4652-81bf-6f836d31a738.png)
