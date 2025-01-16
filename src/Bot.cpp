#include "Server.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

void Server::tellLittleRedRidingHood(int fd) {
  std::string lines[] = {
      "Un jour, une petite fille en capuchon rouge part porter un panier\n",
      "de provisions à sa grand-mère malade. En chemin, elle rencontre un\n",
      "loup rusé qui lui propose un défi : arrivera-t-elle chez sa\n",
      "grand-mère plus vite que lui ? La petite fille s'arrête pour cueillir\n",
      "des fleurs, et le loup arrive le premier. Il se déguise en "
      "grand-mère,\n",
      "mais grâce à l'aide d'un chasseur courageux, le loup est vaincu, et\n",
      "tout finit bien.\n"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::tellThreeLittlePigs(int fd) {
  std::string lines[] = {
      "Trois petits cochons décident de construire chacun une maison pour se\n",
      "protéger du grand méchant loup. Le premier construit en paille, le\n",
      "second en bois, et le troisième en briques. Le loup souffle sur les\n",
      "deux premières maisons et les détruit, mais il ne peut rien contre la\n",
      "maison de briques. Les cochons apprennent l'importance de travailler\n",
      "dur et de bien se préparer.\n"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::tellUglyDuckling(int fd) {
  std::string lines[] = {
      "Un caneton au plumage terne est moqué par les autres animaux. Il se\n",
      "sent seul et triste jusqu'à ce qu'il découvre, en grandissant, qu'il\n",
      "est en réalité un magnifique cygne. Cette histoire enseigne que la\n",
      "beauté intérieure et la patience permettent d'affronter les défis\n",
      "de la vie.\n"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::tellLittleMermaid(int fd) {
  std::string lines[] = {
      "Ariel, une jeune sirène, rêve de découvrir le monde des humains. Elle\n",
      "sauve un prince d'un naufrage et tombe amoureuse. Elle échange sa "
      "voix\n",
      "contre des jambes auprès d'une sorcière des mers. Malgré de nombreux\n",
      "obstacles, Ariel prouve que le courage et l'amour sincère sont les\n",
      "plus grandes forces.\n"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::tellSnowWhite(int fd) {
  std::string lines[] = {
      "Une jeune princesse, Blanche-Neige, est jalousée par sa belle-mère,\n",
      "la méchante reine, à cause de sa beauté. Chassée de chez elle, elle\n",
      "trouve refuge chez sept nains adorables. Mais la reine, déguisée, lui\n",
      "offre une pomme empoisonnée. Heureusement, un prince la réveille avec\n",
      "un baiser d'amour sincère, et ils vivent heureux pour toujours.\n"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::tellHareAndTortoise(int fd) {
  std::string lines[] = {
      "Dans cette fable de La Fontaine, un lièvre arrogant défie une tortue\n",
      "lente à une course. Sûr de gagner, le lièvre fait une sieste en\n",
      "chemin, tandis que la tortue avance lentement mais sûrement. La "
      "tortue\n",
      "finit par remporter la course, montrant que la persévérance est plus\n",
      "importante que la vitesse.\n"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::tellHanselAndGretel(int fd) {
  std::string lines[] = {
      "Un frère et une sœur, Hansel et Gretel, se perdent dans la forêt et\n",
      "découvrent une maison en pain d'épices. Mais la maison appartient à\n",
      "une sorcière qui veut les dévorer. Grâce à leur courage et à leur\n",
      "intelligence, ils réussissent à s'échapper et à retrouver leur chemin\n",
      "vers leur maison, plus unis que jamais.\n"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::tellPussInBoots(int fd) {
  std::string lines[] = {
      "Un jeune homme hérite d'un chat rusé et intelligent. Ce chat, avec "
      "ses\n",
      "bottes et son esprit vif, aide son maître à devenir riche et "
      "respecté.\n",
      "Grâce à des stratagèmes habiles, il impressionne un roi, conquiert un\n",
      "château et fait en sorte que son maître épouse une princesse.\n"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::displayWelcomeMessage(int fd) {
  std::string lines[] = {
      "******************************************************",
      "*                                                    *",
      "*       🌟 Bienvenue sur le Bot d'Histoires 🌟       *",
      "*                                                    *",
      "*    Ici, vous pourrez écouter de magnifiques        *",
      "*    histoires pour petits et grands !               *",
      "*                                                    *",
      "******************************************************",
      "",
      "📚 Sélectionnez une histoire parmi les options ci-dessous :",
      "",
      "[0] Le Petit Chaperon Rouge",
      "[1] Les Trois Petits Cochons",
      "[2] Le Vilain Petit Canard",
      "[3] La Petite Sirène",
      "[4] Blanche-Neige",
      "[5] Le Lièvre et la Tortue",
      "[6] Hansel et Gretel",
      "[7] Le Chat Botté",
      "",
      "******************************************************",
      "",
      "🔒 **Répondez en message privé pour choisir une histoire !** 🔒"};

  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
    std::string message_compose = ":bot PRIVMSG " +
                                  _clients.getClient(fd)->nickname + " :" +
                                  lines[i] + "\n";
    _clients.msgClient(message_compose, _clients.getClient(fd)->nickname, fd);
  }
}

void Server::botResponse(const std::string &msg, int fd) {
  std::stringstream ss(msg);
  int choice;
  ss >> choice;

  if (ss.fail() || !ss.eof()) {
    displayWelcomeMessage(fd);
    return;
  }

  switch (choice) {
  case 0:
    tellLittleRedRidingHood(fd);
    break;
  case 1:
    tellThreeLittlePigs(fd);
    break;
  case 2:
    tellUglyDuckling(fd);
    break;
  case 3:
    tellLittleMermaid(fd);
    break;
  case 4:
    tellSnowWhite(fd);
    break;
  case 5:
    tellHareAndTortoise(fd);
    break;
  case 6:
    tellHanselAndGretel(fd);
    break;
  case 7:
    tellPussInBoots(fd);
    break;
  default:
    displayWelcomeMessage(fd);
  }
}
