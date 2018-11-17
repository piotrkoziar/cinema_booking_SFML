#include "pch.h"
#include "track.h"
#include<cstring>


void track::initialize()
{
	m_text.setString(m_movie->get_name() + " " + std::to_string(m_date->tm_hour) + ":" + std::to_string(m_date->tm_min) + " " + m_room->get_name());
}

track::track(const movie * Movie, const room &Room, tm &date) : m_movie(Movie), m_room(new room(Room)), m_date(&date), m_track_id(++track_id),IDentity(), OnScreen(1000,100.f)
{
	track_v.push_back(this);
	initialize();
}

track::track(const movie * Movie, const room &Room) : m_movie(Movie), m_room(new room(Room)), m_date(new tm), m_track_id(++track_id), IDentity(), OnScreen(1000.f,100.f)
{
	track_v.push_back(this);
}

track::track() : m_track_id(++track_id), m_date(new tm),IDentity(), OnScreen(1000.f, 100.f)
{
	track_v.push_back(this);
}

tm * track::get_date()
{
	return m_date;
}

seat * track::get_selected_seats() const
{
	return m_room->get_selected();
}

void track::draw_room(RenderWindow & target)
{
	m_room->update(target);
	target.draw(*m_room);
}


void track::set_movie(movie *movie)
{
	m_movie = movie;
}

void track::set_room(room * room)
{
	m_room = room;
}


void track::set_date()
{
	std::string tmp;
	bool bad_format;
	do {
		bad_format = false;
		std::cout << "Set date (dd/mm/rrrr): ";
		getline(std::cin, tmp);
		if (tmp.size() == 10) {
			m_date->tm_mday = std::stoi(tmp.substr(0, 2));
			if ((m_date->tm_mday > 31 || m_date->tm_mday < 1))
				bad_format = true;
				m_date->tm_mon = std::stoi(tmp.substr(3, 2)) - 1;
			if (m_date->tm_mon - 1 > 11 || m_date->tm_mon < 0)
				bad_format = true;
				m_date->tm_year = std::stoi(tmp.substr(6, 4)) - 1900;
			if (m_date->tm_year < 0)
				bad_format = true;
		}
		else
			bad_format = true;
	} while (bad_format == true);
}

void track::set_time()
{
	bool bad_format;
	std::string tmp;
	do {
		bad_format = false;
		std::cout << "Set time (hh:mm): ";
		getline(std::cin, tmp);
		if (tmp.size() == 5) {
			m_date->tm_hour = std::stoi(tmp.substr(0, 2));
			if ((m_date->tm_hour > 23 || m_date->tm_hour < 0))
				bad_format = true;
			m_date->tm_min = std::stoi(tmp.substr(3, 2));
			if (m_date->tm_min > 59 || m_date->tm_min < 0)
				bad_format = true;
			if (tmp.substr(2, 1) != ":")
				bad_format = true;
		}
		else
			bad_format = true;
	} while (bad_format == true);
}


void track::show_info() const
{
	std::cout << "Movie: "; m_movie->disp_name();
	//char buff[32];
	//strftime(buff, sizeof buff, "%d/%m/%Y %X\n",&m_date);
	std::cout << std::put_time(m_date, "%d/%m/%Y %X\n");//buff;
	m_room->show();
}


track::~track()
{
	for (unsigned int i = 0; i < track_v.size(); ++i)
	{
		if (track_v[i] == this) {
			track_v.erase(track_v.begin() + i);
			break;
		}
	}
	delete m_room;
}