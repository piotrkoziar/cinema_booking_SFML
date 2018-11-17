

#include "pch.h"
#include <iostream>
#include<SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"room.h"
#include"order.h"
#include"movie.h"
#include"track.h"
#include"user.h"
#include"MyWindow.h"
#include"IDentity.h"
#include"OnScreen.h"

long int IDentity::id_global = 0;
long int order::order_id = 0;
long int movie::movie_id = 0;
long int room::room_id = 0;
long int track::track_id = 0;
long int user::user_id = 0;
std::vector<movie*> movie::movie_v;
std::vector<room*> room::room_v;
std::vector<track*> track::track_v;
std::vector<user*> user::user_v;
std::vector<order*> order::order_v;
//movie, track, order,room should have one basic class

int main()
{
	//declaration of some class objects
	new user("guest");
	new room(5,10,"Room0");
	new room(3, 5, "Room1 (small)");
	new room(7, 14, "Room2 (big)");
	new movie("Star Wars: Episode 1");
	new movie("The Last of Us");
	new movie("The Witcher");
	new movie("Marvel Superheroes");
	tm date4 = { 0, 45 , 15, 6, 11-1, 2018-1900};
	tm date5 = { 0, 15 , 10, 18, 11 - 1, 2018 - 1900 };
	tm date6 = { 0, 0 , 18, 17, 11 - 1, 2018 - 1900 };
	tm date7 = { 0, 30 , 16, 17, 11 - 1, 2018 - 1900 };
	new track(new movie("Gladiator"), *room::room_v[0],date5);
	new track(new movie("Dandelion"), *room::room_v[2], date6);
	new track(movie::return_movie("The Last of Us"), *room::room_v[2], date7);
	//new track(new movie("Batman"), *new room(7, 10, "RoomExtra"), *new tm = { 0 , 30,14,16,11 - 1,2018 - 1900 });
	new track(new movie("The Lord of the Rings: The Fellowship of the Ring"), *room::room_v[1], date7);
	new track(new movie("The Lord of the Rings: Two Towers"), *room::room_v[0], date6);
	//new track(new movie("The Lord of the Rings: The Return of the King"), *room::room_v[2], date5);
	std::string tmp;
	movie * movptr;
	room * roomptr;
	while (true)
	{
		do {
			system("cls");
			std::cout << "Choose:\n1: add room\n2: add movie\n3: add track\ne: exit\n";
			getline(std::cin, tmp);
			switch (tmp[0])
			{
			case '1': {
				new room();
				room::room_v.back()->edit_room();
				break;
			}
			case '2': {
				new movie();
				movie::movie_v.back()->edit_name();
				break;
			}
			case '3': {
				new track();
				track::track_v.back()->set_date();
				track::track_v.back()->set_time();
				std::cout << "Movies: \n";
				for (auto &&i : movie::movie_v) {  //as a function call
					i->disp_name();
					std::cout << " movie id: " << i->get_id() << "\n";
				}
				system("Pause");
				std::cout << "Rooms: \n";
				for (auto &&i : room::room_v) {
					i->disp_name();
					std::cout << " room id: " << i->get_id() << "\n";
				}
				system("Pause");
				do {
					std::cout << "Movie id: ";
					getline(std::cin, tmp);
					movptr = movie::return_movie(std::stol(tmp));
				} while (movptr == nullptr);
				track::track_v.back()->set_movie(movptr);
				do {
					std::cout << "Room id: ";
					getline(std::cin, tmp);
					roomptr = room::return_room(std::stol(tmp));
				} while (roomptr == nullptr);
				track::track_v.back()->set_room(roomptr);
				track::track_v.back()->initialize();
				break;
			}
			default: {
				break;
			}
			}
		} while (tmp[0] != 'e');

		MyWindow menu_window;

		while (menu_window.isOpen())
		{

			while (menu_window.mode1() && menu_window.isOpen())
			{
			}
			while (menu_window.mode2() && menu_window.isOpen())
			{
			}
			while (menu_window.mode3() && menu_window.isOpen())
			{
			}
			while (menu_window.mode4() && menu_window.isOpen())
			{
			}
		}
	}
	return 0;
}



