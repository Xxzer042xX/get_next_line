• Des appels successifs à votre fonction get_next_line() doivent vous permettre de
lire l’intégralité du fichier texte référencé par le descripteur de fichier, une ligne
à la fois.

• Votre programme doit compiler avec l’option : -D BUFFER_SIZE=n

Votre fonction doit retourner la ligne qui vient d’être lue.
S’il n’y a plus rien à lire, ou en cas d’erreur, elle doit retourner NULL

• Assurez-vous que votre fonction se comporte correctement qu’elle lise un fichier
ou qu’elle lise sur l’entrée standar

• Important : Vous devez toujours retourner la ligne qui a été lue suivie du \n la
terminant, sauf dans le cas où vous avez atteint la fin du fichier et que ce dernier
ne se termine pas par un \n.


Il faut pouvoir compiler ce projet avec et sans le -D
Indicateur BUFFER_SIZE en plus des indicateurs habituels. Vous pouvez choisir la valeur par défaut de votre choix.

otre programme sera donc compilé de la manière suivante (exemple ci-dessous
avec une taille de buffer de 42) :
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c

• Nous considérons que get_next_line() a un comportement indeterminé si, entre
deux appels, le fichier pointé par le descripteur de fichier a été modifié, alors que
le premier fichier n’a pas été lu en entier.

Nous considérons aussi que get_next_line() a un comportement indeterminé en
cas de lecture d’un fichier binaire. Cependant, si vous le souhaitez, vous pouvez
rendre ce comportement cohérent.

Votre programme doit lire le moins possible à chaque appel à
get_next_line(). Si vous rencontrez une nouvelle ligne, vous devez
retourner la ligne précédente venant d’être lue.
Ne lisez pas l’intégralité du fichier pour ensuite traiter chaque
ligne.

 La fonction lseek() est interdite.
• Les variables globales sont interdites.


gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 test_get_next_line.c get_next_line.c -o test_get_next_line
