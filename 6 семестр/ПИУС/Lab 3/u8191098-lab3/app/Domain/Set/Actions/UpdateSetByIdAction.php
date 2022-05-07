<?php

namespace App\Domain\Set\Actions;

use App\Models\Set;

class UpdateSetByIdAction
{
    public function execute(int $setId, array $fields):Set
    {
        $set = Set::findOrFail($setId);
        $set->update($fields);

        return $set;
    }
}
