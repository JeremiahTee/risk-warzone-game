////============================================================================
////      Authors                ID           e-mail
////	
////	David Kim           | 27151543 | jykdavid.kim@gmail.com
////	Aryamann Mehra      | 40127106 | aryamanmehra98@gmail.com
////	Jeremiah Tiongson   | 40055477 | jeremiahteee@gmail.com
////	Maxime Johnson      | 40081684 | 11johnson1111@gmail.com
////	Marjolaine Roy      | 40098364 | roy.marjolaine@hotmail.com
////============================================================================
//
//
//#include "Map.h"
//#include "Player.h"
//#include <ostream>
//#include <ctime>
//#include <process.h>
//
//using std::vector;
//using std::cout;
//
//int main()
//{
//	srand((unsigned) time(NULL) * _getpid());
//	
//	Territory* alabama;
//	Territory* boston;
//	Territory* colorado;
//	Territory* delaware;
//	Territory* st_laurent;
//	Territory* mcgill;
//	Territory* concordia;
//
//	vector<Territory*> t1;
//	vector<Territory*> t2;
//
//	alabama = new Territory("Alabama");
//	boston = new Territory("Boston");
//	colorado = new Territory("Colorado");
//	delaware = new Territory("Delaware");
//	st_laurent = new Territory("St-Laurent");
//	mcgill = new Territory("McGill");
//	concordia = new Territory("Concordia");
//
//	t1.push_back(alabama);
//	t1.push_back(boston);
//	t1.push_back(colorado);
//	t1.push_back(delaware);
//
//	t2.push_back(st_laurent);
//	t2.push_back(mcgill);
//	t2.push_back(concordia);
//
//	Hand h1 = Hand(); //empty hand, will test P2's hand for features
//	Hand* hand_one = &h1;
//
//	Hand* hand_two = new Hand(1, 2, 3, 4, 5, 6); //valid hand pointer with actual values for P2
//
//	Player p1 = Player(t1, hand_one, rand() % 100);
//	Player p2 = Player(t2, hand_two, rand() % 100);
//
//	//vector<Territory> p1_terr = p1.getTerritories();
//	//vector<Territory> p2_terr = p2.getTerritories();
//
//	cout << "------------ GETTER: getTerritories() -------------- \n";
//	cout << "Player 1's territories:\n";
//	
//	//for(auto it = p1_terr.begin(); it != p1_terr.end(); ++it)
//	//{
//	//cout << it->getName() << std::endl;
//	//}
//
//	//cout << "\nPlayer 2's territories:\n";
//
//	//for (auto it = p2_terr.begin(); it != p2_terr.end(); ++it)
//	//{
//	//	cout << it->getName() << std::endl;
//	//}
//
//	//vector<Territory> p1_terr_to_attack = p1.toAttack();
//	//vector<Territory> p2_terr_to_defend = p2.toDefend();
//
//	cout << "\n------------ METHOD: toAttack() -------------- \n\n";
//	cout << "Player 1's territories to be attacked:\n";
//	
//	/*for (auto it = p1_terr_to_attack.begin(); it != p1_terr_to_attack.end(); ++it)
//	{
//		cout << it->getName() << std::endl;
//	}
//
//	cout << "------------ METHOD: toDefend() -------------- \n\n";
//	cout << "Player 2's territories to be defended:\n";
//
//	for (auto it = p2_terr_to_defend.begin(); it != p2_terr_to_defend.end(); ++it)
//	{
//		cout << it->getName() << std::endl;
//	}*/
//
//	cout << "------------ METHOD: issueOrder() -------------- \n\n";
//	cout << "Player 1 has issued an order:\n";
//
//	p1.issueOrder();
//
//	cout << "\n------------ Creating Deck in order to test functionalities -------------- \n";
//	
//	int spy(1);
//	int bomb(2);
//	int reinforcement(3);
//	int blockade(4);
//	int airlift(5);
//	int diplomacy(6);
//
//	Deck* dp = new Deck(spy, bomb, reinforcement, blockade, airlift, diplomacy); //deck pointer
//
//	for (int i = 0; i < 7; i++)
//	{
//		int cardType(0);
//		cardType = dp->draw(dp);
//		hand_two->addToHand(cardType, hand_two);
//	}
//
//	cout << "\n------------ Printing out Deck in order to test ostream functionality -------------- \n";
//	
//	//cout << *dp;
//
//	cout << "\n------------ Printing out Hand in order to test ostream functionality -------------- \n";
//
//	//cout << *hand_two;
//
//	cout << "\n------------ Printing out Player 2 to show ostream functionality -------------- \n";
//
//	cout << p2;
//
//    // Pointer cleanup
//	delete alabama;
//	delete boston;
//	delete colorado;
//	delete delaware;
//	delete st_laurent;
//	delete mcgill;
//	delete concordia;
//	delete dp;
//	delete hand_two;
//	
//	return 0;
//}