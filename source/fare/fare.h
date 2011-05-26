#pragma once

#include "../utils/csv.h"
#include <boost/graph/adjacency_list.hpp> 

/// Définit l'état courant
struct State {
    /// Dernier ticket utilisé
    std::string ticket;

    /// Durée depuis le dernier ticket acheté (en secondes)
    int duration;

    /// Dernier mode utilisé
    std::string mode;

    /// Dernière zone utilisée
    std::string zone;

    /// Dernier endroit où à eu lieu l'achat
    std::string stop_area;

    std::string line;

    /// Nombre de changements effectués
    int changes;

    /// Réseau utilisé
    std::string network;

    State() : duration(0), changes(0) {}

    bool operator==(const State & other) const {
        return ticket==other.ticket && duration==other.duration && mode == other.mode
                && zone==other.zone && stop_area == other.stop_area && line == other.line
                && changes == other.changes && network == other.network;
    }


    bool operator<(const State & other) const {
        return ticket<other.ticket && duration<other.duration && mode < other.mode
                && zone<other.zone && stop_area<other.stop_area && line<other.line
                && changes<other.changes && network<other.network;
    }
};


/// Type de comparaison possible entre un arc et une valeur
enum Comp_e { Less, Greater, Equal, Nil};

/// Définit un arc et les conditions pour l'emprunter
/// Les conditions peuvent être : prendre u
struct Condition {
    /// Valeur à que doit respecter la condition
    std::string condition_value;

    /// Ticket à acheter pour prendre cet arc
    /// Chaîne vide si rien à faire
    std::string ticket;
    
    /// Opérateur de comparaison
    /// Nil s'il n'y a pas de restriction
    Comp_e comparaison;

    /// Valeur à comparer
    std::string value;
};

/// Représente un transition possible et l'achat éventuel d'un billet
struct Transition {
    State source;
    State target;
    Condition cond;
    std::string ticket;
    float value;
};

/// Parse un état
State parse_state(const std::string & state);

/// Parse une condition de passage
Condition parse_condition(const std::string & condition);

/// Parse une ligne complète
Transition parse_transition(const std::string & transition);