#pragma once
class Status
{
	private:
		std::string _nom;			// Nom du Status
		int _duree;					// Durée d'éffet du Status
		float _selfHeal;			// Probabilité d'auto gérison

		std::string _alteredStat;	// Nom de la stat qui aura un malus
		int _alterValue;			// Valeur de reduction de la stat

	public:
		Status();
		~Status();
		void init(std::string nom, int duree, float selfHeal, std::string alteredStat, int alterValue);

		std::string getNom();
		int getDuree();
		float getSelfHeal();
		std::string getAlteredStat();
		int getAlterValue();

		void setNom(std::string nom);
		void setDuree(int duree);
		void setSelfHeal(float probHeal);
		void setAlteredStat(std::string nomStat);
		void setAlterValue(int alterVal);
};

