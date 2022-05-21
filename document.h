//Вставьте сюда своё решение из урока «‎Очередь запросов».‎
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "search_server.h"


struct Document {
	Document(); 
	Document(int id, double relevance, int rating);
	        
	    int id=0;
	    double relevance = 0.0;
	    int rating = 0;
	};

// document.h
enum class DocumentStatus {
	ACTUAL,
	IRRELEVANT,
	BANNED,
	REMOVED,
};

std::ostream& operator<<(std::ostream& out, const Document& document);

void PrintDocument(const Document& document);

void PrintMatchDocumentResult(int document_id, const std::vector<std::string>& words, DocumentStatus status);

void AddDocument(SearchServer& search_server, int document_id, const std::string& document,
    DocumentStatus status, const std::vector<int>& ratings);

void FindTopDocuments(const SearchServer& search_server, const std::string& raw_query);

void MatchDocuments(const SearchServer& search_server, const std::string& query);