## Introduction 
Lanmodulin is a very impressive protein, with high specificity for lanthanides, heat stability, and an impressive resilience to dramatic pH change. It also possesses 3 active binding pockets which are agents in the formation of the proteins tertiary structures upon binding with a ligand. However, in industrial applications, the optimization of operational efficiency is imperative to maximizing profit margins, which lead our team to pursue methods of improving lanmodulin's lanthanides binding capacity. We used two approaches to this problem, a mutant protein library which focused on optimizing the protein's binding affinity across its operational pH range, and a multilayered genetic algorithm for functionalizing lanmodulin’s fourth binding pocket.

## Mutant Subspace Exploration
When mutating proteins, there exists a subspace of all possible sequence permutations. Within that subspace there are different smaller subspaces of protein sequences which can be categorized and accessed through targeted mutation. For instance, the amino acid sequence “AA” (alanine-alanine) has 21 possible amino acids which could replace each of the alinines in the sequence, giving a very large subspace of potential two amino acid sequences. However, if we wanted to access a more specific subspace of mutations, we could allow each amino acid to only change to the amino acids within its family, so A could change to either V or L. This type of targeted mutation allows us to intelligently access specific areas of the total subspace, which helps reduce our computational load.

Using this principle, we designed our protein mutation systems to access different parts of this total subspace to maximize our chances of improving binding capacity while minimizing computational load.

## Mutant Protein Library 
When building our mutant protein library (MLP), we started off by finding the amino acids in lanmodulin’s structure with the greatest impact on structural integrity. We achieved this by running the amino acid sequence of lanmodulin through the HotSpot Wizard Web Client, which then identified structurally significant hotspots [1]. With these values, we then constructed a list of protein mutants with point mutations.

![image](https://github.com/wcjona/Optimal-Linkers/assets/46095400/79913a57-a455-4be4-995c-ef00709d3f30)

*Figure 1.This table displays 7 of our most optimal mutations and their binding affinity values at different pH levels.*

In order to assess the differences in binding affinity for mutants over the operational pH range of lanmodulin, we had to pre-process their 3D structures for different pH levels and then assess their binding affinity. To accomplish this we made pdb files for each mutation by applying the corresponding point mutation to the wild type lanmodulin pdb. We then used ProteinPrepare, a program designed for the optimization of protein hydrogen networks prior to molecular dynamics simulations hosted by PlayMolecule, to process the pdb for different pH levels [2].

Having used ProteinPrepare to process each mutant at different pH levels, we ran said models through AutoDock 4, a program from the AutoDock suite for assessing the binding affinity of a given protein and ligand [3]. With our binding affinities for the different mutants at different pH levels we were able to identify 7 mutants which improved the binding affinity of lanmodulin over the entire operational pH range of the protein, which can be found in figure 1. Of these mutants we chose two to be submitted to the iGEM [registry](https://2021.igem.org/Team:Calgary/Part_Collection). Due to lab constraints we were not able to produce either of these proteins for in vitro validation, however assessing the viability of these proteins would be an important step in validating our protein mutation process.

Overall, our MPL was a very selective mutation method based on generalized structurally important amino acids, meaning it accessed a very small subspace of potential mutations in the whole protein. While improving the binding affinity of lanmodulin could improve the efficiency of the extraction process, the greatest room for improvement lies in its one pseudo binding pocket. This is where our three EF hand mutationing and optimizing softwares come into play. With a more specific target, our mutations processes can cover a greater portion of the subspace. By accessing and scoring this subset of the mutation subspace, we could activate the pseudobinding pocket and enable the protein to bind up to 4 lanthanides at once.

## Intro to Genetic Algorithms 
In an ideal world, we would produce a mutated sequence for every possible permutation of the amino acids in the fourth EF hand of lanmodulin and assess the sequence's effectiveness to find the best possible EF hand. However, it's simply too computationally expensive to assess every possible permutation of an EF hand sequence. Therefore, we designed our mutation systems to focus on specific subspaces of complete sequence subspace that had the greatest potential for improving the EF hand. This process involved developing two more basic mutation systems and using their outputs as initialization values for our later mentioned genetic algorithm.

The first workflow we designed was built on a family conservation mutation model. In effect, we created every possible mutation of the fourth binding pocket for lanmodulin that still maintained the family of each amino acid. This meant that, for instance, a negatively charged AA could only be replaced by another negatively charged amino acid. Each sequence was then scored using our EF hand identification software Efhe, which assessed the viability of the sequence as an EF hand. The sequence was then scored based on the number of aspartic or glutamic acids it contained, as these are the amino acids that contribute to the negative electromagnetic field that enables the binding characteristic of EF hands. With a bias towards highly scoring sequences, 12 of these potential mutants were selected to be used as the initial population for our genetic algorithm. The most successful mutant can be found on the registry HERE.

Our second software was a predictive model developed by approximating the ‘average’ amino acids in each position of an EF hand. Averages were based on data retrieved from uniprot, from the same data set used in our EF Hand Evaluator [4]. The goal with this type of sample space investigation was to find the most generic sequence of an EF hand, an average point in the sequence space. These generic EF hand sequences were then used in our genetic algorithm to provide a baseline for a generalized structure of the negative electrostatic region of the binding pocket. The 12 most likely were selected to be added to the initial population for the genetic algorithm in conjunction with the 12 from the family conservation exploration.

Finally, our genetic algorithm takes a set of sequences as its starting point and continuously mutates and scores these sequences to find an optimized EF hand sequence. Our initialization step involved taking 12 protein sequences from each of our previous mutation algorithms, and taking the original fourth binding pocket from Lanmodulin. By including the original unviable binding pocket we are able to ensure that the algorithm only provides enhanced scores. The outputs will never be worse than the original. These 25 sequences were scored using our EF hand finder deep learning algorithm to verify that each sequence was in fact an EF hand, then using an electromagnetic charge assessment function to score the different sequences based on the number of electronegative amino acids in the protein, as well as the sequences overall homology when compared to the other three binding pockets of lanmodulin. This homology score weighted mutants differently based on their similarity with the three binding pockets, with homology with the first and third binding pocket being weighted higher than homology with the second due to the fact that one and three are more different from one another. This opened up a greater proportion of the subspace to our algorithm, preventing overfitting to the very similar first and second binding pockets. After scoring and ranking the 25 potential EF hand sequences, the top 10 sequences were saved and the bottom 15 were labeled for intense mutation. The sequences ranked from second to tenth underwent moderate point mutations, with the highest ranking sequence being kept unchanged to ensure its genetic information was maintained. Each round of mutation consisted of a crossover phase, where pieces of the top 10 amino acids were randomly chosen and placed into the bottom 15 amino acid sequences. After this crossing over was completed, the sequences were subjected to random point mutations once again. Again, the bottom 15 sequences were subjected to a greater amount of mutations than were the top 10.

The endpoint was decided based on convergence. In our implementation this was set to the point where the top ranked EF hands fitness score was not changed for 50 mutation cycles. The final sequence who ‘won’ the genetic algorithm was then selected for use by the wetlab.

## Conclusion 
As a result of this system, we have developed five potential mutated versions of lanmodulin using different mutation algorithms to access different sample spaces of all potential mutations of lanmodulin’s forth binding pocket. The next steps for verification of the sequences would involve structure prediction modeling and molecular dynamic simulation for these mutated proteins to verify their stability and binding affinity. After this in silico verification process, in vitro experiments would be conducted to establish experimental proof of the greater binding ability of this fully functionalizing lanmodulin binding pocket mutant.

## References
Sumbalova L, Stourac J, Martinek T, Bednar D, Damborsky J. HotSpot Wizard 3.0: web server for automated design of mutations and smart libraries based on sequence input information. Hotspot wizard. 2018 Jul 2 [accessed 2021 Oct 21]. https://loschmidt.chemi.muni.cz/hotspotwizard/

Martinez-Rosell G, Giorgino T, Fabritiis GD. PlayMolecule ProteinPrepare: A Web Application for Protein Preparation for Molecular Dynamics Simulations. ACS Publications. 2017 Jun 8 [accessed 2021 Oct 21]. https://pubs.acs.org/doi/10.1021/acs.jcim.7b00190

Morris GM, R H. AutoDock4 and AutoDockTools4: Automated Docking with Selective Receptor Flexibility. Autodock. 2009 Dec 30 [accessed 2021 Oct 21]. http://autodock.scripps.edu/resources/references

Bateman A, Martin M-J, Orchard S, Magrane M, Agivetova R, Ahmad S, Alpi E, Bowler-Barnett EH, Britto R, Bursteinas B, et al. 2020. Uniprot: The Universal Protein Knowledgebase in 2021. Nucleic Acids Research 49.

Van Der Spoel D;Lindahl E;Hess B;Groenhof G;Mark AE;Berendsen HJ; Gromacs: Fast, flexible, and Free. Journal of computational chemistry. 2005 Dec 26 [accessed 2021 Oct 21]. https://pubmed.ncbi.nlm.nih.gov/16211538/
