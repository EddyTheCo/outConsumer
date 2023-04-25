#include"outconsumer.hpp"
#include"encoding/qbech32.hpp"
#include"QJsonDocument"
#include"QJsonObject"

using namespace qiota;

void OutConsumer::consume(std::vector<qiota::Node_output>  outs, const QJsonValue & address, QVector<quint32> subpath,QString amountneedit)
{
    const quint64 amount_need_it=amountneedit.toULongLong();
    const auto addrptr=qblocks::Address::from_(address);


    auto bundle= (addrptr->type()==qblocks::Address::Ed25519_typ)?Account::get_addr(subpath):AddressBundle(addrptr);

    bundle.consume_outputs(outs,amount_need_it);


    QJsonArray aliasad;
    for(const auto& v: bundle.alias_outputs)
    {
        aliasad.push_back(Address::Alias(v->get_id())->get_Json());
    }

    QJsonArray nftad;
    for(const auto& v: bundle.nft_outputs)
    {
        nftad.push_back(Address::NFT(v->get_id())->get_Json());
    }

    QJsonArray foundryid;
    for(const auto& v: bundle.foundry_outputs)
    {
        foundryid.push_back(v->get_id().toHexString());
    }
    QJsonObject var;
    var.insert("alias",aliasad);
    var.insert("nft",nftad);
    var.insert("foundry",foundryid);
    var.insert("amount",QString::number(bundle.amount));
    emit finish(var,bundle);
}
