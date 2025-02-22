#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
using namespace std;
int num = 60;
int mx = 0;
vector<vector<sf::RectangleShape>>matrs(num, vector<sf::RectangleShape>(num));
vector<vector<int>>matr(num, vector<int>(num, 0));
vector<vector<bool>>vis(num, vector<bool>(num, 0));
map<int, set<pair<int, int>>>mp;
pair<int, int>dir[4] = { {0,1},{1,0},{-1,0},{0,-1} };
void dfs(int x, int y, int val)
{
	if (vis[x][y])return;
	vis[x][y] = 1;
	matr[x][y] = val;
	mp[val].insert({ x,y });
	mx = max(mx, val);
	for (auto& e : dir)
	{
		int dx = x + e.first, dy = y + e.second;
		if (dx >= num || dy >= num || dx < 0 || dy < 0)continue;
		if (vis[dx][dy] == 1)continue;
		//cout << vis[dx][dy];
		cout << val<<" ";
		dfs(dx, dy, val + 1);
	}
}
void help()
{
	srand(time(NULL));
	//num = (rand() % 60) + 1;
	int ri = rand() % num, rj = rand() % num;
	vis.clear();
	matr.clear();
	vis.resize(num, vector<bool>(num, 0));
	matr.resize(num, vector<int>(num, 0));
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			vis[i][j] = 0;
			matr[i][j] = 0;
		}
	}
	mx = 0;
	mp.clear();
	matrs.resize(num, vector<sf::RectangleShape>(num));
	dfs(10, 0, 0);
}
void bfs()
{
	srand(time(NULL));
	//num = (rand() % 60) + 1;
	int ri = rand() % num, rj = rand() % num;
	vis.clear();
	matr.clear();
	vis.resize(num, vector<bool>(num, 0));
	matr.resize(num, vector<int>(num, 0));
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			vis[i][j] = 0;
			matr[i][j] = 0;
		}
	}
	mx = 0;
	mp.clear();
	matr[ri][rj] = 0;
	queue<vector<int>>qe;
	qe.push({ ri,rj,0 });
	while (!qe.empty())
	{
		vector<int>three = qe.front();
		int x = three[0], y = three[1], val = three[2];
		//cout << x << " " << y << "\n";
		vis[x][y] = 1;
		matr[x][y] = val;
		mp[val].insert({ x,y });
		//cout << qe.size()<<endl;
		qe.pop();
		//cout << qe.size() << endl;
		for (auto& e : dir)
		{
			int dx = x + e.first, dy = y + e.second;
			if (dx >= num || dy >= num || dx < 0 || dy < 0)continue;
			if (vis[dx][dy] == 1)continue;
			//cout << vis[dx][dy];
			//cout << val<<" ";
			qe.push({ dx,dy,val + 1 });
			vis[dx][dy] = 1;
		}
		//cout << val << "\n";
		mx = max(val, mx);
		//if (qe.size() > 3num)break;
	}
	matrs.resize(num, vector<sf::RectangleShape>(num));
}
class support
{
private:
	//variables
	//window
	sf::RenderWindow* window;
	sf::Event eevee;
	sf::VideoMode videoMode;
	//Mouse position
	sf::Vector2i MousePosWindow;
	sf::Vector2f mousePosView;
	//Resources
	sf::Font font;
	//Text
	//Variables
	set<vector<int>>trips;
	map<int, set<pair<int, int>>>::iterator timer;
	int itimer;
	void initWindow();
	void initVar();
	void initFonts();
	void initText();
public:
	bool destroy = 0;
	support();//Constructor
	virtual ~support();//Destructor
	//Accessors
	const bool running() const;
	//Functions
	vector<int> randtrip();
	void pollEvents();
	void updateMousePositions();
	void update();
	void reset();
	void updategrid(int val);
	void renderrect(sf::RenderTarget& target);
	void render();
};
//Private functions
void support::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Happy_New_Year_2025", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void support::initVar()
{
	itimer = 0;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			matrs[i][j].setPosition(sf::Vector2f(i * (600.f/(num*1.f)) + 100.f, j * (600.f / (num * 1.f)) + 100.f));
			matrs[i][j].setSize(sf::Vector2f((600.f / (num * 1.f)), (600.f / (num * 1.f))));
			matrs[i][j].setFillColor(sf::Color::Black);
			matrs[i][j].setOutlineColor(sf::Color::White);
			matrs[i][j].setOutlineThickness(1.f);
		}
	}
}

void support::initFonts()
{
	if (this->font.loadFromFile("fonts/Raleway-Bold.ttf"))
	{
		std::cout << "ERROR:support::::INITFONTS::Failed to load font" << "\n";
	}
}

void support::initText()
{
	
}


support::support()
{
	this->initWindow();
	this->initFonts();
	this->initVar();
	this->initText();
}

support::~support()
{
	delete this->window;
}
//Accessors
const bool support::running() const
{
	return this->window->isOpen();
}

//Functions
vector<int> support::randtrip()
{
	//Better visuals
	/*if (itimer % 3 == 0)return{255,0,0};
	else if (itimer % 3 == 1)return{ 0,255,0 };
	else return { 0,0,255 };*/
	//dfs: single color
	//return { 255,0,0 };
	do {
		int a = rand() % 255, b = rand() % 255, c = rand() % 255;
		if (trips.find({a,b,c}) == trips.end())
		{
			trips.insert({ a,b,c });
			return {a,b,c };
		}
	} while (true);
}
void support::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->eevee))
	{
		switch (this->eevee.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->eevee.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;
			}
		}
	}
}
void support::updateMousePositions()
{
	/*return void
	Updates the mouse position:
	Mouse pos relative to window(vector2i)*/
	this->MousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->MousePosWindow);
}

//ctrl + . or > key on function in h file to auto define in cpp file
void support::update()
{
	this->pollEvents();
	this->updateMousePositions();
	//Update mouse position
	//Relative to the window
	if (itimer>mx)
	{
		//cout << mx << "\n";
		reset();
		itimer = 0;
	}
	updategrid(itimer);
	itimer++;
	sf::Clock clock;
	while (true)
	{
		sf::Time time = clock.getElapsedTime();
		if (time.asSeconds() >= 0.01f)break;
	}
}

void support::updategrid(int val)
{
	auto b = randtrip();
	for (auto& e :mp[val])
	{
		matrs[e.first][e.second].setFillColor(sf::Color(b[0], b[1], b[2]));
	}
}
void support::reset()
{
	trips.clear();
	bfs();
	//help();
	/*for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			matrs[i][j].setFillColor(sf::Color::Black);
		}
	}*/
	initVar();
}
void support::renderrect(sf::RenderTarget& target)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			target.draw(matrs[i][j]);
		}
	}
}



void support::render()
{
	/*
	* return void
	 -clear old frame
	 -render objects
	 -display the new window

	renders the support objects

	*/
	//color(r,g,b,transparency(alpha))
	this->window->clear(sf::Color());
	//Draw support
	this->renderrect(*this->window);
	this->window->display();
}

int main()
{
	srand(time(NULL));
		int ri = rand() % num, rj = rand() % num;
		vis.resize(num, vector<bool>(num, 0));
		matr.resize(num, vector<int>(num, 0));
		mx = 0;
		mp.clear();
		matr[ri][rj] = 0;
		queue<vector<int>>qe;
		qe.push({ ri,rj,0 });
		while (!qe.empty())
		{
			vector<int>three = qe.front();
			int x = three[0], y = three[1], val = three[2];
			//cout << x << " " << y << "\n";
			vis[x][y] = 1;
			matr[x][y] = val;
			mp[val].insert({ x,y });
			//cout << qe.size()<<endl;
			qe.pop();
			//cout << qe.size() << endl;
			for (auto& e : dir)
			{
				int dx = x + e.first, dy = y + e.second;
				if (dx >= num || dy >= num || dx < 0 || dy < 0)continue;
				if (vis[dx][dy] == 1)continue;
				//cout << vis[dx][dy];
				//cout << val<<" ";
				qe.push({ dx,dy,val + 1 });
				vis[dx][dy] = 1;
			}
			mx = max(val, mx);
			//if (qe.size() > 3num)break;
		}
		support scr;
		while (scr.running() && !scr.destroy)
		{
			//cout << "hello";
			scr.update();
			scr.render();
		}
	return 0;
}