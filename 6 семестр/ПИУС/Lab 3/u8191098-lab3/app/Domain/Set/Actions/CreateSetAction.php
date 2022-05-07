<?php

namespace App\Domain\Set\Actions;

use App\Models\Set;

class CreateSetAction
{
    public function execute(array $fields): Set
    {
        return Set::create($fields);
    }
}
